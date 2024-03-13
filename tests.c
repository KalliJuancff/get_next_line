#include <fcntl.h>		// open, O_RDONLY
#include "get_next_line.h"
#include "assertions.h"

void simular_escritura_desde_teclado(char *texto)
{
	int pipefd[2];

	// Creamos un pipe
	if (pipe(pipefd) == -1)
	{
		perror("Error al ejecutar la función 'pipe'.\n");
		exit (-1);
	}

	int len = ft_strlen(texto);
	// Escribimos en el extremo de lectura del pipe el texto que corresponda
	write(pipefd[1], texto, len);

	// Redirigimos la entrada estándar al extremo de lectura del pipe
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror ("Error al ejecutar la función 'dup2'.\n");
		exit (-1);
	}

	// Cerramos el extremo de escritura del pipe ya que no lo necesitamos
	close(pipefd[1]);

	// Mostramos el texto que simulamos que se escribe desde el teclado
	char *dup_texto;
	dup_texto = duplicar_cadena_sin_intros(texto);
	printf(TITULO("Contenido fichero: "));
	printf("%s\n", dup_texto);
	free (dup_texto);
}

void test1()
{
	// ¡Ya no necesito ficheros reales!
	//     int fd = open("1.txt", O_RDONLY);
	simular_escritura_desde_teclado("12345");

	// NOTA:
	// Teóricamente, tendría que acabar llamando a la función 'free' para cada una de las líneas válidas obtenidas,
	// pero no lo hago y 'leaks' tampoco se queja...
	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "12345");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);

	// close(fd);
}

void test2()
{
	simular_escritura_desde_teclado("123");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "123");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
}

void test3()
{
	simular_escritura_desde_teclado("123\n");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "123\n");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
}
void test4()
{
	simular_escritura_desde_teclado("1234567890123");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "1234567890123");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
}

void test5()
{
	simular_escritura_desde_teclado("123456789012345");

	assertEqualString(get_next_line(STDIN_FILENO), "123456789012345");
	assertEqualString(get_next_line(STDIN_FILENO), NULL);
}


void test6()
{
	simular_escritura_desde_teclado("12\n45");

	assertEqualString(get_next_line(STDIN_FILENO), "12\n");
	assertEqualString(get_next_line(STDIN_FILENO), "45");
	assertEqualString(get_next_line(STDIN_FILENO), NULL);
}

int main()
{
	printf(TITULO("TEST1:")"\n");
	test1();

	printf(TITULO("TEST2:")"\n");
	test2();

	printf(TITULO("TEST3:")"\n");
	test3();

	printf(TITULO("TEST4:")"\n");
	test4();

/*
	printf(TITULO("TEST5:")"\n");
	test5();

	printf(TITULO("TEST6:")"\n");
	test6();
*/

	return (0);
}
