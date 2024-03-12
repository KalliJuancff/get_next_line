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
	// int fd = open("2.txt", O_RDONLY);
	simular_escritura_desde_teclado("123");

	assertEqualString(get_next_line(STDIN_FILENO), "123");
	assertEqualString(get_next_line(STDIN_FILENO), NULL);

	// close(fd);
}

int main()
{
	printf("TEST1:\n");
	test1();

	printf("TEST2:\n");
	test2();

	return (0);
}
