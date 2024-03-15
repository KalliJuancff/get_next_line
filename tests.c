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
	simular_escritura_desde_teclado("123");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "123");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);

	// close(fd);
}

void test2a()
{
	simular_escritura_desde_teclado("1234567");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "1234567");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
}

void test2b()
{
	simular_escritura_desde_teclado("12345");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "12345");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
}

/*
void test2a()
{
	simular_escritura_desde_teclado("123\n");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "123\n");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
}

void test4b()
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
	simular_escritura_desde_teclado("1234567890");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "1234567890");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
}

void test5b()
{
	simular_escritura_desde_teclado("123456789012345");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "123456789012345");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
}

void test6()
{
	simular_escritura_desde_teclado("");

	char *linea1;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
}

void test7()
{
	simular_escritura_desde_teclado("12\n45");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "12\n");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), "45");
	assertEqualString((linea3 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);
}
*/

int main()
{
	printf(TITULO("TEST1:")"\n");
	test1();

	printf(TITULO("TEST2a:")"\n");
	test2a();

/*
	printf(TITULO("TEST2b:")"\n");
	test2b();

	printf(TITULO("TEST3:")"\n");
	test3();

	printf(TITULO("TEST4:")"\n");
	test4();

	printf(TITULO("TEST4b:")"\n");
	test4b();

	printf(TITULO("TEST5:")"\n");
	test5();

	printf(TITULO("TEST5b:")"\n");
	test5b();

	printf(TITULO("TEST6:")"\n");
	test6();

	printf(TITULO("TEST7:")"\n");
	test7();
*/

	return (0);
}
