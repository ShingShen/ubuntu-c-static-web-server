#include "request.h"
#include "response.h"

void *request_handler(void *arg)
{
    int client_sock = *((int *)arg);
    char req_line[SMALL_BUF];
    FILE *client_read;
    FILE *client_write;

    char method[10];
    char ct[15];
    char file_name[30];

    client_read = fdopen(client_sock, "r");
    client_write = fdopen(dup(client_sock), "w");
    fgets(req_line, SMALL_BUF, client_read);

    if (strstr(req_line, "HTTP/") == NULL) {
        send_error(client_write);
        fclose(client_read);
        fclose(client_write);
        return;
    }

    strcpy(method, strtok(req_line, " /"));
    strcpy(file_name, strtok(NULL, " /"));
    strcpy(ct, content_type(file_name));

    if (strcmp(method, "GET") != 0) {
        send_error(client_write);
        fclose(client_read);
        fclose(client_write);
        return;
    }

    fclose(client_read);
    send_data(client_write, ct, file_name);
}