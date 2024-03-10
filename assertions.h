#ifndef ASSERTIONS_H
# define ASSERTIONS_H

#include <stdio.h>		// printf, NULL
#include <string.h>		// strcmp, NULL

#define SUCCESS(text) "\033[32m" text "\033[0m"
#define FAIL(text) "\033[31m" text "\033[0m"

void assertEqualString(char *s1, char *s2);

#endif
