#include "cachelab.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

int hit_count, miss_count, evict_count; // global counter to print
int s, S, b, B, E, t;
bool is_verbose = false;
char* file;
int cur_time; // timer for LRU

typedef struct cache_block {
    bool valid;
    unsigned int timestamp; // LRU
    unsigned int tag;
} cache_block;

cache_block** cache_array;
// creating a array of M[S][E] LRU head
void init ()
{
    S = 1 << s;
    B = 1 << b;
    cur_time = 0;
    cache_array = (cache_block**) malloc(sizeof(cache_block*) * S);
    for (int i = 0; i < S; i++) {
        cache_array[i] = (cache_block*) malloc(sizeof(cache_block) * E);
        memset(cache_array[i], 0, sizeof(cache_block) * E);
    }
    return;
}

void clear_up()
{
    for (int i = 0; i < S; i++) {
        free(cache_array[i]);
    }
    free(cache_array);
}

/* parser deal with input */
void print_helpmessage()
{
    return;
}

void parser(int argc, char** argv) 
{
    int opt; 
    while ((opt = getopt(argc, argv, "vhs:E:b:t:")) != -1) {
        switch (opt) {
            case 's':
                s = atoi(optarg);
                break;
            case 'E':
                E = atoi(optarg);
                break;
            case 'b':
                b = atoi(optarg);
                break;
            case 't':
                file = (char*) malloc(1 + sizeof(optarg));
                strcpy(file, optarg);
                break;  
            case 'h':
                print_helpmessage();
                exit(0); 
                break;
            case 'v':
                is_verbose = true;
                break;
            default:
                break;
        }
    }
}
/* LRU */

/* formal execution */
/*  hints:
    1. block is not important, since assume all ops in boundary
    2. using LRU to evict line(defined by E)
    3. dealing with 32-bit address
    4. S,L,M performs nearly the same logic; except m has a extra hit
                                   
                            / 2a. if hit, hit_count++                                                       \            
S/L : 1. search-all-line ->                                                                                  5. update timestamp       
                            \ 2. miss, miss_count++; 3. if full, erase LRU, evict_count++; 4. update cache /
M:  Do a S/L, and a extra hit_count++

*/
void update(unsigned int address, char identifier)
{
    unsigned int cur_tag = address >> (s + b);
    unsigned int cur_s = (address & ((1 << (s + b)) - (1 << b))) >> b;
    bool hit_target = false;
    // record an empty line to fill this cache, if it empty_line < 0, the set is full
    // this parameters would notice the final block tobe modified 
    int empty_line = -1; 
    int lru_to_evict = -1; // if set is full, the cache block to erase
    int oldest_time = 1e9+7; // oldest time
    // step 1.
    for (int i = 0; i < E; i++) {
        if (cache_array[cur_s][i].valid) { 
            if (cache_array[cur_s][i].tag == cur_tag) { // hit
                hit_target = true;
                empty_line = i;
                break;
            }

            if (cache_array[cur_s][i].timestamp < oldest_time) {
                lru_to_evict = i;
                oldest_time = cache_array[cur_s][i].timestamp;
            }

        } else {
            empty_line = i;
        }
    }
    
    // handle traversal consequence
    if (hit_target) {  // step 2a.
        hit_count++;
    } else {
        miss_count++; // step 2.

        if (empty_line < 0) { // step 3.
            evict_count++;
            assert(lru_to_evict >= 0);
            empty_line = lru_to_evict;
        }
        // step 4.
        cache_array[cur_s][empty_line].valid = true;
        cache_array[cur_s][empty_line].tag = cur_tag;
    }
    // step 5.
    cache_array[cur_s][empty_line].timestamp = cur_time;

    if (identifier == 'M') {
        hit_count++;
    }
    return;
}

void deal_with_text()
{
    FILE* tfile;
    tfile = fopen(file, "r");
    assert (tfile != NULL);
    char identifier; unsigned int address; 
    while(fscanf(tfile, " %c %x, %*d", &identifier, &address) > 0) {
        cur_time++;
        if (identifier == 'I') {
            continue;
        }
        update(address, identifier);  
    }
    fclose(tfile);
}

// file-read\write
int main(int argc, char** argv)
{
    parser(argc, argv);
    init();
    deal_with_text();
    printSummary(hit_count, miss_count, evict_count);
    clear_up();
    return 0;
}
