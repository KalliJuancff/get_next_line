#include "get_next_line.h"
#include "assertions.h"

char *duplicar_cadena_sin_intros(char *cadena)
{
	if (cadena == NULL)
		return (ft_strdup("NULL"));

	int i = 0;
	int num_intros = 0;
	while (cadena[i] != '\0')
	{
		if (*cadena == '\n')
			num_intros++;
		i++;
	}

	char *retorno;
	i = 0;
	retorno = malloc(ft_strlen(cadena) + num_intros + 1 * sizeof(char));
	while (*cadena)
	{
		if (*cadena == '\n')
		{
			retorno[i] = '\\';
			i++;
			retorno[i] = 'n';
		}
		else
			retorno[i] = *cadena;

		cadena++;
		i++;
	}
	retorno[i] = '\0';
	return (retorno);
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

	free(dup_actual);
	free(dup_esperada);
}
