#ifndef REQUEST_H
#define REQUEST_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 1024
#define SMALL_BUF 100

void *request_handler(void *);

#endif