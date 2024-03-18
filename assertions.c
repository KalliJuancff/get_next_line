#include "get_next_line.h"
#include "assertions.h"

int obtener_numero_intros(char *texto)
{
	int i = 0;
	int retorno = 0;

	while (texto[i] != '\0')
	{
		if (*texto == '\n')
			retorno++;
		i++;
	}

	return (retorno);
}

char *duplicar_cadena_sin_intros(char *texto)
{
	if (texto == NULL)
		return (ft_strjoin("(NULL)", ""));

	int i = 0;
	char *retorno = malloc(ft_strlen(texto) + obtener_numero_intros(texto) + 2 + 1 * sizeof(char));

	retorno[i++] = '\"';
	while (*texto != '\0')
	{
		if (*texto == '\n')
		{
			retorno[i++] = '\\';
			retorno[i] = 'n';
		}
		else
			retorno[i] = *texto;

		texto++;
		i++;
	}
	retorno[i++] = '\"';
	retorno[i] = '\0';

	return (retorno);
}

void assertEqualString(char *actual, char *esperada)
{
	int error;

	if (actual == NULL && esperada != NULL)
		error = 1;
	else if (actual != NULL && esperada == NULL)
		error = 1;
	else if (actual == NULL && esperada == NULL)
		error = 0;
	else
		// actual != NULL && esperada != NULL
		error = (strcmp(actual, esperada) == 0) ? 0 : 1;

	char *dup_actual = duplicar_cadena_sin_intros(actual);
	char *dup_esperada = duplicar_cadena_sin_intros(esperada);
	if (error)
		printf("%s: Se encontró el valor %s pero se esperaba %s.\a\n", ERRONEO("KO"), dup_actual, dup_esperada);
	else
		printf("%s: Se encontró el valor esperado %s.\n", CORRECTO("OK"), dup_esperada);
	free(dup_actual);
	free(dup_esperada);
}
