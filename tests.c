#include <fcntl.h>		// open, O_RDONLY
#include "get_next_line.h"
#include "assertions.h"

void simular_escritura_desde_teclado(char *texto)
{
	int pipefd[2];

	// Creamos un pipe
	if (pipe(pipefd) == -1)
	{
		perror("Error al ejecutar el comando 'pipe'.\n");
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

	// Cerramos el extremo de escritura del pipe, ya que no lo necesitamos
	close(pipefd[1]);
}

void test1()
{
	// ¡Ya no necesito ficheros reales!
	//     int fd = open("1.txt", O_RDONLY);
	simular_escritura_desde_teclado("12345");

	assertEqualString(get_next_line(STDIN_FILENO), "12345");
	assertEqualString(get_next_line(STDIN_FILENO), NULL);

	// close(fd);
}

void test2()
{
	simular_escritura_desde_teclado("123");

	assertEqualString(get_next_line(STDIN_FILENO), "123");
	assertEqualString(get_next_line(STDIN_FILENO), NULL);
}

void test3()
{
	simular_escritura_desde_teclado("123\n");

	assertEqualString(get_next_line(STDIN_FILENO), "123\n");
	assertEqualString(get_next_line(STDIN_FILENO), NULL);
}
void test4()
{
	simular_escritura_desde_teclado("1234567890123");

	assertEqualString(get_next_line(STDIN_FILENO), "1234567890123");
	assertEqualString(get_next_line(STDIN_FILENO), NULL);
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

	printf(TITULO("TEST5:")"\n");
	test5();

	printf(TITULO("TEST6:")"\n");
	test6();

	return (0);
}
