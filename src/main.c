#include <arpa/inet.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include "request.h"

int main(int argc, char *argv[]) 
{
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    unsigned int client_addr_size;
    pthread_t t_id;

    unsigned int server_port = 8080;
    if (argc > 1) {
        if (sscanf(argv[1], "%u", &server_port) == 0 || server_port > 65535) {
            fprintf(stderr, "error: invalid command line argument, using default port 8080.\n");
            server_port = 8080;
        }
    }

    server_sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&server_addr, 0, sizeof(server_addr));
    
    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port        = htons(server_port);

    if(bind(server_sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
        fprintf(stderr, "bind() error");
        exit(1);
    }

    if(listen(server_sock, 20) == -1) {
        fprintf(stderr, "listen() error");
        exit(1);
    }

    while(1) {
        client_addr_size = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_addr_size);
        printf("Connection Request : %s:%d\n",
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        pthread_create(&t_id, NULL, request_handler, &client_sock);
        pthread_detach(t_id);
    }

    close(server_sock);
    return 0;
}