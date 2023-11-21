#include <stdio.h>
#include <csapp.h>
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

void doit(int clientfd) 
{
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char hostname[MAXLINE], port[MAXLINE];
    // 1.read request line, check method, uri, version, check if valid
    // 2.read request-header, get host, port
    // 3.open connect to the server 
        /*
            Open connection to server at <hostname, port>
            proxyfd = open_clientfd(hostname, port)

        */
    // 4.read other request to fullfil buf, also append what's needed(version, suffix)
    // 5.write to the server and get respond
    // 7.write to clientfd
    // 8.close proxyfd

}