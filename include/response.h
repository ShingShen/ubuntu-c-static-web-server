#ifndef RESPONSE_H
#define RESPONSE_H

#include "request.h"

void send_data(FILE *, char *, char *);
char *content_type(char *);
void send_error(FILE *);

#endif