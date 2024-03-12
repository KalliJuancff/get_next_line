#include "get_next_line.h"
#include "assertions.h"

void reemplazarIntros(char *s)
{
	if (s == NULL)
		return;

	while (*s != '\0')
	{
		if (*s == '\n')
			*s = '$';
		s++;
	}
}

char *duplicar_cadena_sin_intros(char *cadena)
{
	char *result;

	if (cadena == NULL)
		return (NULL);

	result = ft_strdup(cadena);
	reemplazarIntros(result);
	return (result);
}

void assertEqualString(char *s1, char *s2)
{
	int error = 0;
	char *dup_s1, *dup_s2;

	if (s1 == NULL && s2 != NULL)
		error = 1;
	else if (s1 != NULL && s2 == NULL)
		error = 1;
	else if (s1 == NULL && s2 == NULL)
		error = 0;
	else if (strcmp(s1, s2) != 0)
		error = 1;

	dup_s1 = duplicar_cadena_sin_intros(s1);
	dup_s2 = duplicar_cadena_sin_intros(s2);

	if (error)
		printf("%s: Las cadenas '%s' y '%s' *NO* son iguales.\n", ERRONEO("KO"), dup_s1, dup_s2);
	else
		printf("%s: Las cadenas '%s' y '%s' son iguales.\n", CORRECTO("OK"), dup_s1, dup_s2);

	if (dup_s1 != NULL)
		free(dup_s1);
	if (dup_s2 != NULL)
		free(dup_s2);
}
