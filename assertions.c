#include <stdio.h>		// printf
#include <stdlib.h>		// NULL
#include <string.h>		// strcmp
#include "assertions.h"

void assertEqualString(char *s1, char *s2)
{
	int error = 0;

	if (s1 == NULL && s2 != NULL)
		error = 1;
	else if (s1 != NULL && s2 == NULL)
		error = 1;
	else if (s1 == NULL && s2 == NULL)
		error = 0;
	else if (strcmp(s1, s2) != 0)
		error = 1;

	if (error)
		printf("%s: Las cadenas '%s' y '%s' *NO* son iguales.\n", FAIL("KO"), s1, s2);
	else
		printf("%s: Las cadenas '%s' y '%s' son iguales.\n", SUCCESS("OK"), s1, s2);
}
