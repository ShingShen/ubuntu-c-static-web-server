#include <pthread.h>

#include "request.h"

int main(int argc, char *argv[]) 
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    unsigned int clnt_adr_size;
    pthread_t t_id;

    uint16_t server_port = 8080;
    if (argc > 1) {
        if (sscanf(argv[1], "%u", &server_port) == 0 || server_port > 65535) {
            fprintf(stderr, "error: invalid command line argument, using default port 8080.\n");
            server_port = 8080;
        }
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serv_adr, 0, sizeof(serv_adr));
    
    serv_adr.sin_family      = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port        = htons(server_port);

    if(bind(serv_sock, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) == -1) {
        fprintf(stderr, "bind() error");
        exit(1);
    }

    if(listen(serv_sock, 20) == -1) {
        fprintf(stderr, "listen() error");
        exit(1);
    }

    while(1) {
        clnt_adr_size = sizeof(clnt_adr);
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_adr, &clnt_adr_size);
        printf("Connection Request : %s:%d\n",
               inet_ntoa(clnt_adr.sin_addr), ntohs(clnt_adr.sin_port));
        pthread_create(&t_id, NULL, request_handler, &clnt_sock);
        pthread_detach(t_id);
    }

    close(serv_sock);
    return 0;
}