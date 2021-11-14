#ifndef __CLI_H_
#define __CLI_H_

#include <stdbool.h>

#define VERSION "v0.1"

bool quit;

void print_version();
void print_help();
void handle_args(int *, char **);

#endif