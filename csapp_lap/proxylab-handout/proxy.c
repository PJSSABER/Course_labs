#include <stdio.h>
#include <csapp.h>
#include <stdbool.h>
/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400

/* You won't lose style points for including this long line in your code */
static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";


/*
    basic functions:
    1. listen for incoming connections on a port 
    2. Once a connection is established, your proxy should read the entirety of the request
from the client and parse the request
        if the client has sent a valid HTTP request;
            establish its own connection to the appropriate web server then request the object the client specified. 
            important: forward HTTP/1.0 always
            Host header
            Connection: close
            Proxy-Connection: close 
            user_agent_hdr
        else 
            error and return
    3. your proxy should read the server’s response and forward it to the client

    4. should never prematurely abort due to a malformed request
    5. Your proxy must properly function whether or not the port number is included in the URL(by default is port 80)
    6(done). Your proxy should accept a command line argument specifying the listening port number for your proxy.
*/
typedef struct sockaddr_storage sockaddr_storage;

void doit(int fd);
int debug;
void yiyu_debug(char *s)
{
    if (debug) {
        printf("%s", s);
    }
}

int main(int argc, char **argv)
{
    int listenfd, connectfd;
    sockaddr_storage clientaddr; socklen_t clientlen;
    // variable declare
    if (argc != 2) {
        unix_error("usage: just specify a port\n");
	    exit(1);
    }

    listenfd = Open_listenfd(argv[1]);
    while (1) {
        connectfd = Accept(listenfd, &clientaddr, &clientlen);
        doit(connectfd);
        Close(connectfd);
    }

    printf("%s", user_agent_hdr);
    return 0;
}

void parse_uri(char *uri, char *hostname, char *port)
{
    char *colon = strstr(uri, ":");
    if (colon) {
        strcpy(port, colon+1);
    } else { // no port
        strcpy(port, "80");
    }

    uint32_t uri_len = strlen(uri);
    bool flag = false;
    for (int i = 0; i < uri_len; i++) {
        if (flag ) {
            if (uri[i] == '/') {
                break;
            }
            *port = uri[i];
            port++;
        } else {
            if (uri[i] == 'w') {
                flag = true;
                *port = uri[i];
                port++;
            }
        }
    }
}

void doit(int clientfd) 
{
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE], hostname[MAXLINE],//if not specified in header, parse from uri 
    port[MAXLINE];//if not specified in header, 80 
    char send_msg[MAXLINE];
    rio_t rio;
    Rio_readinitb(&rio, clientfd);
    // 1.read request line, check method, uri, version, check if valid
    if (!Rio_readlineb(&rio, buf, MAXLINE)) {
        return;
    }
    yiyu_debug(buf);
    sscanf(buf, "%s %s %s", method, uri, version);

    if (strcasecmp(method, "GET")) {
        printf("Not support HTTP type, support only GET!");
        return;
    } else {
        sprintf(send_msg, method, " ", uri);
    }
    // check port
    parse_uri(uri, hostname, port);
    sprintf(send_msg, " HTTP/1.0 \r\n");
    // 2.read request-header, check if host exist
    
    // 3.read other request to fullfil buf, also append what's needed(version, suffix)
    // 4.open connect to the server 
    /*
        Open connection to server at <hostname, port>
        proxyfd = open_clientfd(hostname, port)

    */
    // 5.write to the server and get respond
    // 7.write to clientfd
    // 8.close proxyfd

}