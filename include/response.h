#ifndef RESPONSE_H
#define RESPONSE_H

#include "request.h"

extern void send_data(FILE *, char *, char *);
extern char *content_type(char *);
extern void send_error(FILE *);

#endif