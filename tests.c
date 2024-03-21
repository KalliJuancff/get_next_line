#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"
#include "assertions.h"

const char *_nombre_fichero = "temp_file.txt";
int _fd;

int crear_y_escribir_en_fichero_temporal(char *texto)
{
	FILE *fichero;

	fichero = fopen(_nombre_fichero, "w");
	if (fichero == NULL)
	{
		fprintf(stderr, "El fichero temporal '%s' no pudo ser creado: %s\n", _nombre_fichero, strerror(errno));
		exit(-1);
	}
	if (fprintf(fichero, "%s", texto) < 0)
	{
		fprintf(stderr, "No se pudo escribir en el fichero temporal '%s': %s\n", _nombre_fichero, strerror(errno));
		exit(-1);
	}
	if (fclose(fichero) != 0)
	{
		fprintf(stderr, "No se pudo cerrar el fichero temporal '%s': %s\n", _nombre_fichero, strerror(errno));
		exit(-1);
	};

	printf(TITULO("Contenido fichero: "));
	char *dup_texto;
	dup_texto = duplicar_cadena_sin_intros(texto);
	printf("%s\n", dup_texto);
	free(dup_texto);

	return (open(_nombre_fichero, O_RDONLY));
}


void test0a()
{
	_fd = crear_y_escribir_en_fichero_temporal("\n\n\n\n\n");

	char *linea1, *linea2, *linea3, *linea4, *linea5, *linea6;
	assertEqualString((linea1 = get_next_line(_fd)), "\n");
	assertEqualString((linea2 = get_next_line(_fd)), "\n");
	assertEqualString((linea3 = get_next_line(_fd)), "\n");
	assertEqualString((linea4 = get_next_line(_fd)), "\n");
	assertEqualString((linea5 = get_next_line(_fd)), "\n");
	assertEqualString((linea6 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);
	free(linea4);
	free(linea5);
	free(linea6);

	unlink(_nombre_fichero);
	close(_fd);
}


void test1a()
{
	_fd = crear_y_escribir_en_fichero_temporal("12345");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(_fd)), "12345");
	assertEqualString((linea2 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);

	unlink(_nombre_fichero);
	close(_fd);
}

void test1b()
{
	_fd = crear_y_escribir_en_fichero_temporal("123");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(_fd)), "123");
	assertEqualString((linea2 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);

	unlink(_nombre_fichero);
	close(_fd);
}

void test1c()
{
	_fd = crear_y_escribir_en_fichero_temporal("1234567890");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(_fd)), "1234567890");
	assertEqualString((linea2 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);

	unlink(_nombre_fichero);
	close(_fd);
}

void test1d()
{
	_fd = crear_y_escribir_en_fichero_temporal("1234567");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(_fd)), "1234567");
	assertEqualString((linea2 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);

	unlink(_nombre_fichero);
	close(_fd);
}

void test1e()
{
	_fd = crear_y_escribir_en_fichero_temporal("123456789012345");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(_fd)), "123456789012345");
	assertEqualString((linea2 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);

	unlink(_nombre_fichero);
	close(_fd);
}

void test1f()
{
	_fd = crear_y_escribir_en_fichero_temporal("1234567890123");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(_fd)), "1234567890123");
	assertEqualString((linea2 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);

	unlink(_nombre_fichero);
	close(_fd);
}


void test2a()
{
	_fd = crear_y_escribir_en_fichero_temporal("12\n45");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(_fd)), "12\n");
	assertEqualString((linea2 = get_next_line(_fd)), "45");
	assertEqualString((linea3 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);

	unlink(_nombre_fichero);
	close(_fd);
}

void test2b()
{
	_fd = crear_y_escribir_en_fichero_temporal("1\n3");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(_fd)), "1\n");
	assertEqualString((linea2 = get_next_line(_fd)), "3");
	assertEqualString((linea3 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);

	unlink(_nombre_fichero);
	close(_fd);
}

void test2c()
{
	_fd = crear_y_escribir_en_fichero_temporal("12\n4567890");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(_fd)), "12\n");
	assertEqualString((linea2 = get_next_line(_fd)), "4567890");
	assertEqualString((linea3 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);

	unlink(_nombre_fichero);
	close(_fd);
}

void test2d()
{
	_fd = crear_y_escribir_en_fichero_temporal("12\n4567");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(_fd)), "12\n");
	assertEqualString((linea2 = get_next_line(_fd)), "4567");
	assertEqualString((linea3 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);

	unlink(_nombre_fichero);
	close(_fd);
}

void test2e()
{
	_fd = crear_y_escribir_en_fichero_temporal("12\n456789012345");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(_fd)), "12\n");
	assertEqualString((linea2 = get_next_line(_fd)), "456789012345");
	assertEqualString((linea3 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);

	unlink(_nombre_fichero);
	close(_fd);
}

void test2f()
{
	_fd = crear_y_escribir_en_fichero_temporal("12\n4567890123");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(_fd)), "12\n");
	assertEqualString((linea2 = get_next_line(_fd)), "4567890123");
	assertEqualString((linea3 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);

	unlink(_nombre_fichero);
	close(_fd);
}


void test3a()
{
	_fd = crear_y_escribir_en_fichero_temporal("1234\n");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(_fd)), "1234\n");
	assertEqualString((linea2 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);

	unlink(_nombre_fichero);
	close(_fd);
}

void test3b()
{
	_fd = crear_y_escribir_en_fichero_temporal("12\n");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(_fd)), "12\n");
	assertEqualString((linea2 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);

	unlink(_nombre_fichero);
	close(_fd);
}

void test3c()
{
	_fd = crear_y_escribir_en_fichero_temporal("123456789\n");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(_fd)), "123456789\n");
	assertEqualString((linea2 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);

	unlink(_nombre_fichero);
	close(_fd);
}

void test3d()
{
	_fd = crear_y_escribir_en_fichero_temporal("123456\n");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(_fd)), "123456\n");
	assertEqualString((linea2 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);

	unlink(_nombre_fichero);
	close(_fd);
}

void test3e()
{
	_fd = crear_y_escribir_en_fichero_temporal("12345678901234\n");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(_fd)), "12345678901234\n");
	assertEqualString((linea2 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);

	unlink(_nombre_fichero);
	close(_fd);
}

void test3f()
{
	_fd = crear_y_escribir_en_fichero_temporal("123456789012\n");

	char *linea1, *linea2;
	assertEqualString((linea1 = get_next_line(_fd)), "123456789012\n");
	assertEqualString((linea2 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);

	unlink(_nombre_fichero);
	close(_fd);
}


void test3g()
{
	_fd = crear_y_escribir_en_fichero_temporal("123456789012\n4");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(_fd)), "123456789012\n");
	assertEqualString((linea2 = get_next_line(_fd)), "4");
	assertEqualString((linea3 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);

	unlink(_nombre_fichero);
	close(_fd);
}

void test3h()
{
	_fd = crear_y_escribir_en_fichero_temporal("123456789012\n45");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(_fd)), "123456789012\n");
	assertEqualString((linea2 = get_next_line(_fd)), "45");
	assertEqualString((linea3 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);

	unlink(_nombre_fichero);
	close(_fd);
}

void test3i()
{
	_fd = crear_y_escribir_en_fichero_temporal("12345678901234\n1");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(_fd)), "12345678901234\n");
	assertEqualString((linea2 = get_next_line(_fd)), "1");
	assertEqualString((linea3 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);

	unlink(_nombre_fichero);
	close(_fd);
}


void test4a()
{
	_fd = crear_y_escribir_en_fichero_temporal("\n2345");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(_fd)), "\n");
	assertEqualString((linea2 = get_next_line(_fd)), "2345");
	assertEqualString((linea3 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);

	unlink(_nombre_fichero);
	close(_fd);
}

void test4b()
{
	_fd = crear_y_escribir_en_fichero_temporal("\n23");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(_fd)), "\n");
	assertEqualString((linea2 = get_next_line(_fd)), "23");
	assertEqualString((linea3 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);

	unlink(_nombre_fichero);
	close(_fd);
}

void test4c()
{
	_fd = crear_y_escribir_en_fichero_temporal("\n234567890");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(_fd)), "\n");
	assertEqualString((linea2 = get_next_line(_fd)), "234567890");
	assertEqualString((linea3 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);

	unlink(_nombre_fichero);
	close(_fd);
}

void test4d()
{
	_fd = crear_y_escribir_en_fichero_temporal("\n234567");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(_fd)), "\n");
	assertEqualString((linea2 = get_next_line(_fd)), "234567");
	assertEqualString((linea3 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);

	unlink(_nombre_fichero);
	close(_fd);
}

void test4e()
{
	_fd = crear_y_escribir_en_fichero_temporal("\n23456789012345");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(_fd)), "\n");
	assertEqualString((linea2 = get_next_line(_fd)), "23456789012345");
	assertEqualString((linea3 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);

	unlink(_nombre_fichero);
	close(_fd);
}

void test4f()
{
	_fd = crear_y_escribir_en_fichero_temporal("\n234567890123");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(_fd)), "\n");
	assertEqualString((linea2 = get_next_line(_fd)), "234567890123");
	assertEqualString((linea3 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);

	unlink(_nombre_fichero);
	close(_fd);
}


void test5c()
{
	_fd = crear_y_escribir_en_fichero_temporal("1234567\n90");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(_fd)), "1234567\n");
	assertEqualString((linea2 = get_next_line(_fd)), "90");
	assertEqualString((linea3 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);

	unlink(_nombre_fichero);
	close(_fd);
}

void test5d()
{
	_fd = crear_y_escribir_en_fichero_temporal("123456\n8");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(_fd)), "123456\n");
	assertEqualString((linea2 = get_next_line(_fd)), "8");
	assertEqualString((linea3 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);

	unlink(_nombre_fichero);
	close(_fd);
}

void test5e()
{
	_fd = crear_y_escribir_en_fichero_temporal("123456789012\n45");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(_fd)), "123456789012\n");
	assertEqualString((linea2 = get_next_line(_fd)), "45");
	assertEqualString((linea3 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);

	unlink(_nombre_fichero);
	close(_fd);
}

void test5f()
{
	_fd = crear_y_escribir_en_fichero_temporal("12345678901\n3");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(_fd)), "12345678901\n");
	assertEqualString((linea2 = get_next_line(_fd)), "3");
	assertEqualString((linea3 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);

	unlink(_nombre_fichero);
	close(_fd);
}


void test7c()
{
	_fd = crear_y_escribir_en_fichero_temporal("12\n4567\n90");

	char *linea1, *linea2, *linea3, *linea4;
	assertEqualString((linea1 = get_next_line(_fd)), "12\n");
	assertEqualString((linea2 = get_next_line(_fd)), "4567\n");
	assertEqualString((linea3 = get_next_line(_fd)), "90");
	assertEqualString((linea4 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);
	free(linea4);

	unlink(_nombre_fichero);
	close(_fd);
}

void test7d()
{
	_fd = crear_y_escribir_en_fichero_temporal("12\n456\n8");

	char *linea1, *linea2, *linea3, *linea4;
	assertEqualString((linea1 = get_next_line(_fd)), "12\n");
	assertEqualString((linea2 = get_next_line(_fd)), "456\n");
	assertEqualString((linea3 = get_next_line(_fd)), "8");
	assertEqualString((linea4 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);
	free(linea4);

	unlink(_nombre_fichero);
	close(_fd);
}

void test7e()
{
	_fd = crear_y_escribir_en_fichero_temporal("12\n456789012\n45");

	char *linea1, *linea2, *linea3, *linea4;
	assertEqualString((linea1 = get_next_line(_fd)), "12\n");
	assertEqualString((linea2 = get_next_line(_fd)), "456789012\n");
	assertEqualString((linea3 = get_next_line(_fd)), "45");
	assertEqualString((linea4 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);
	free(linea4);

	unlink(_nombre_fichero);
	close(_fd);
}

void test7f()
{
	_fd = crear_y_escribir_en_fichero_temporal("12\n45678901\n3");

	char *linea1, *linea2, *linea3, *linea4;
	assertEqualString((linea1 = get_next_line(_fd)), "12\n");
	assertEqualString((linea2 = get_next_line(_fd)), "45678901\n");
	assertEqualString((linea3 = get_next_line(_fd)), "3");
	assertEqualString((linea4 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);
	free(linea4);

	unlink(_nombre_fichero);
	close(_fd);
}


void test8c()
{
	_fd = crear_y_escribir_en_fichero_temporal("12\n456789\n");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(_fd)), "12\n");
	assertEqualString((linea2 = get_next_line(_fd)), "456789\n");
	assertEqualString((linea3 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);

	unlink(_nombre_fichero);
	close(_fd);
}

void test8d()
{
	_fd = crear_y_escribir_en_fichero_temporal("12\n4567\n");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(_fd)), "12\n");
	assertEqualString((linea2 = get_next_line(_fd)), "4567\n");
	assertEqualString((linea3 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);

	unlink(_nombre_fichero);
	close(_fd);
}

void test8e()
{
	_fd = crear_y_escribir_en_fichero_temporal("12\n45678901234\n");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(_fd)), "12\n");
	assertEqualString((linea2 = get_next_line(_fd)), "45678901234\n");
	assertEqualString((linea3 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);

	unlink(_nombre_fichero);
	close(_fd);
}

void test8f()
{
	_fd = crear_y_escribir_en_fichero_temporal("12\n456789012\n");

	char *linea1, *linea2, *linea3;
	assertEqualString((linea1 = get_next_line(_fd)), "12\n");
	assertEqualString((linea2 = get_next_line(_fd)), "456789012\n");
	assertEqualString((linea3 = get_next_line(_fd)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);

	unlink(_nombre_fichero);
	close(_fd);
}


void test99()
{
	_fd = crear_y_escribir_en_fichero_temporal("");

	char *linea1;
	assertEqualString((linea1 = get_next_line(_fd)), NULL);

	free(linea1);

	unlink(_nombre_fichero);
	close(_fd);
}


int main()
{
	printf(TITULO("TEST0a (Francinette):")"\n");
	test0a();


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


	printf(TITULO("TEST3g:")"\n");
	test3g();

	printf(TITULO("TEST3h:")"\n");
	test3h();

	printf(TITULO("TEST3i:")"\n");
	test3i();


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


	printf(TITULO("TEST5c:")"\n");
	test5c();

	printf(TITULO("TEST5d:")"\n");
	test5d();

	printf(TITULO("TEST5e:")"\n");
	test5e();

	printf(TITULO("TEST5f:")"\n");
	test5f();


	printf(TITULO("TEST7c:")"\n");
	test7c();

	printf(TITULO("TEST7d:")"\n");
	test7d();

	printf(TITULO("TEST7e:")"\n");
	test7e();

	printf(TITULO("TEST7f:")"\n");
	test7f();


	printf(TITULO("TEST8c:")"\n");
	test8c();

	printf(TITULO("TEST8d:")"\n");
	test8d();

	printf(TITULO("TEST8e:")"\n");
	test8e();

	printf(TITULO("TEST8f:")"\n");
	test8f();


	printf(TITULO("TEST99:")"\n");
	test99();


	return (0);
}
