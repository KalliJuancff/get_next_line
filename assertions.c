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

void assertEqualString(char *actual, char *esperada)
{
	int error = 0;
	char *dup_actual, *dup_esperada;

	if (actual == NULL && esperada != NULL)
		error = 1;
	else if (actual != NULL && esperada == NULL)
		error = 1;
	else if (actual == NULL && esperada == NULL)
		error = 0;
	else if (strcmp(actual, esperada) != 0)
		error = 1;

	dup_actual = duplicar_cadena_sin_intros(actual);
	dup_esperada = duplicar_cadena_sin_intros(esperada);

	if (error)
		printf("%s: Se encontró el valor '%s', pero se esperaba '%s'.\n", ERRONEO("KO"), dup_actual, dup_esperada);
	else
		printf("%s: Se encontró el valor esperado '%s'.\n", CORRECTO("OK"), dup_esperada);

	if (dup_actual != NULL)
		free(dup_actual);
	if (dup_esperada != NULL)
		free(dup_esperada);
}
