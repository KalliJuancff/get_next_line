#ifndef ASSERTIONS_H
# define ASSERTIONS_H

#include <stdio.h>		// printf, NULL
#include <string.h>		// strcmp, NULL

#define CODIGO_ESCAPE_RESET "\033[0m"

#define CORRECTO(text) "\033[32m" text CODIGO_ESCAPE_RESET
#define ERRONEO(text) "\033[31m" text CODIGO_ESCAPE_RESET
#define TITULO(text) "\033[1;37m" text CODIGO_ESCAPE_RESET

void assertEqualString(char *s1, char *s2);

#endif
