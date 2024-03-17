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


void test1a()
{
	// ¡Ya no necesito ficheros reales!
	//     int fd = open("1.txt", O_RDONLY);
	simular_escritura_desde_teclado("12345");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "12345");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);

	// close(fd);
}

void test1b()
{
	simular_escritura_desde_teclado("123");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "123");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
}

void test1c()
{
	simular_escritura_desde_teclado("1234567890");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "1234567890");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
}

void test1d()
{
	simular_escritura_desde_teclado("1234567");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "1234567");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
}

void test1e()
{
	simular_escritura_desde_teclado("123456789012345");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "123456789012345");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
}

void test1f()
{
	simular_escritura_desde_teclado("1234567890123");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "1234567890123");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
}


void test2a()
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

void test2b()
{
	simular_escritura_desde_teclado("1\n3");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "1\n");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), "3");
	assertEqualString((linea3 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);
}

void test2c()
{
	simular_escritura_desde_teclado("12\n4567890");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "12\n");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), "4567890");
	assertEqualString((linea3 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);
}

void test2d()
{
	simular_escritura_desde_teclado("12\n4567");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "12\n");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), "4567");
	assertEqualString((linea3 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);
}

void test2e()
{
	simular_escritura_desde_teclado("12\n456789012345");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "12\n");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), "456789012345");
	assertEqualString((linea3 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);
}

void test2f()
{
	simular_escritura_desde_teclado("12\n4567890123");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "12\n");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), "4567890123");
	assertEqualString((linea3 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);
}


void test3a()
{
	simular_escritura_desde_teclado("1234\n");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "1234\n");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
}

void test3b()
{
	simular_escritura_desde_teclado("12\n");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "12\n");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
}

void test3c()
{
	simular_escritura_desde_teclado("123456789\n");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "123456789\n");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
}

void test3d()
{
	simular_escritura_desde_teclado("123456\n");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "123456\n");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
}

void test3e()
{
	simular_escritura_desde_teclado("12345678901234\n");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "12345678901234\n");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
}

void test3f()
{
	simular_escritura_desde_teclado("123456789012\n");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "123456789012\n");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
}


void test4a()
{
	simular_escritura_desde_teclado("\n2345");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "\n");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), "2345");
	assertEqualString((linea3 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);
}

void test4b()
{
	simular_escritura_desde_teclado("\n23");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "\n");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), "23");
	assertEqualString((linea3 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);
}

void test4c()
{
	simular_escritura_desde_teclado("\n234567890");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "\n");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), "234567890");
	assertEqualString((linea3 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);
}

void test4d()
{
	simular_escritura_desde_teclado("\n234567");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "\n");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), "234567");
	assertEqualString((linea3 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);
}

void test4e()
{
	simular_escritura_desde_teclado("\n23456789012345");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "\n");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), "23456789012345");
	assertEqualString((linea3 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);
}

void test4f()
{
	simular_escritura_desde_teclado("\n234567890123");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "\n");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), "234567890123");
	assertEqualString((linea3 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);
}


/*
void test3b()
{
	simular_escritura_desde_teclado("12\n4567");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "12\n");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), "4567");
	assertEqualString((linea3 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);
}


void test3d()
{
	simular_escritura_desde_teclado("12\n456\n7");

	char *linea1, *linea2, *linea3, *linea4;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "12\n");
	assertEqualString((linea2 = get_next_line(STDIN_FILENO)), "456\n");
	assertEqualString((linea3 = get_next_line(STDIN_FILENO)), "7");
	assertEqualString((linea4 = get_next_line(STDIN_FILENO)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);
	free(linea4);
}

void test2a()
{
	simular_escritura_desde_teclado("123\n");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(STDIN_FILENO)), "123\n");
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
*/

int main()
{
	printf(TITULO("TEST1a:")"\n");
	test1a();

	printf(TITULO("TEST1b:")"\n");
	test1b();

	printf(TITULO("TEST1c:")"\n");
	test1c();

	printf(TITULO("TEST1d:")"\n");
	test1d();

	printf(TITULO("TEST1e:")"\n");
	test1e();

	printf(TITULO("TEST1f:")"\n");
	test1f();


	printf(TITULO("TEST2a:")"\n");
	test2a();

	printf(TITULO("TEST2b:")"\n");
	test2b();

	printf(TITULO("TEST2c:")"\n");
	test2c();

	printf(TITULO("TEST2d:")"\n");
	test2d();

	printf(TITULO("TEST2e:")"\n");
	test2e();

	printf(TITULO("TEST2f:")"\n");
	test2f();


	printf(TITULO("TEST3a:")"\n");
	test3a();

	printf(TITULO("TEST3b:")"\n");
	test3b();

	printf(TITULO("TEST3c:")"\n");
	test3c();

	printf(TITULO("TEST3d:")"\n");
	test3d();

	printf(TITULO("TEST3e:")"\n");
	test3e();

	printf(TITULO("TEST3f:")"\n");
	test3f();


	printf(TITULO("TEST4a:")"\n");
	test4a();

	printf(TITULO("TEST4b:")"\n");
	test4b();

	printf(TITULO("TEST4c:")"\n");
	test4c();

	printf(TITULO("TEST4d:")"\n");
	test4d();

	printf(TITULO("TEST4e:")"\n");
	test4e();

	printf(TITULO("TEST4f:")"\n");
	test4f();


	return (0);
}
