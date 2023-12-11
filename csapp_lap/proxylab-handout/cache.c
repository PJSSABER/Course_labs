#include <stdio.h>
#include "csapp.h"
#include <stdbool.h>
/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400


/*
    implement a thread-safe circular queue
    and its method.
    其实可能用hash+linked-list方式会更好，锁更小 Or ?? 再想想 这种链表的锁好像不是那么简单啊！！
*/

typedef struct cache_block {  
    char key[MAXLINE]; 
    char val[MAX_OBJECT_SIZE];
} cache_block;

const int cache_size = 10;

typedef struct cache {  
    cache_block buff[cache_size];
    int head, tail, size; // [head, tail]; when size == 0 (tail < head), it's empty
    int read_cnt;
    sem_t mutex, w;
} cache;

cache* init() {
    cache *ptr = (cache*)malloc(sizeof(cache));
    if (ptr == NULL) {
        exit(1);
    }

    (*ptr).head = 0;
    (*ptr).tail = -1;
    (*ptr).size = 0;
    (*ptr).read_cnt = 0;
    Sem_init(&(*ptr).mutex, 1, 1);
    Sem_init(&(*ptr).w, 1, 1);
    return ptr;
}

void reader_lock(cache *ptr) {

}

void reader_unlock(cache *ptr) {

}

void writer_lock(cache *ptr) {

}

void writer_unlock(cache *ptr) {

}

char* check_cache(char *target, cache *ptr) {
    char *ret = NULL;
    reader_lock(ptr);
    for (int i = 0; i < (*ptr).size; i++) {    // using a hashmap can save time here. 但是一把大锁还是需要的
        int idx = ((*ptr).head + i) % cache_size;
        if (strcmp(target, (*ptr).buff[idx].key) == 0) {     
            ret = (*ptr).buff[idx].val;
            break;
        }
    }
    reader_unlock(ptr);
    return ret;
}

void push_cache();

void pop_cache();