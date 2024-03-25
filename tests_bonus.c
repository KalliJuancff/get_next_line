#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"
#include "assertions.h"


int crear_y_escribir_en_fichero_temporal(char *nombre_fichero, char *texto)
{
	FILE *fichero;

	fichero = fopen(nombre_fichero, "w");
	if (fichero == NULL)
	{
		fprintf(stderr, "El fichero temporal '%s' no pudo ser creado: %s\n", nombre_fichero, strerror(errno));
		exit(-1);
	}
	if (fprintf(fichero, "%s", texto) < 0)
	{
		fprintf(stderr, "No se pudo escribir en el fichero temporal '%s': %s\n", nombre_fichero, strerror(errno));
		exit(-1);
	}
	if (fclose(fichero) != 0)
	{
		fprintf(stderr, "No se pudo cerrar el fichero temporal '%s': %s\n", nombre_fichero, strerror(errno));
		exit(-1);
	};

	printf("Contenido fichero '%s': ", nombre_fichero);
	char *dup_texto;
	dup_texto = duplicar_cadena_sin_intros(texto);
	printf("%s\n", dup_texto);
	free(dup_texto);

	return (open(nombre_fichero, O_RDONLY));
}


void test1()
{
	char *nombre_fichero1 = "temp_file1.txt";
	char *nombre_fichero2 = "temp_file2.txt";
	char *nombre_fichero3 = "temp_file3.txt";
	char *nombre_fichero4 = "temp_file4.txt";
	char *nombre_fichero5 = "temp_file5.txt";
	int fd1 = crear_y_escribir_en_fichero_temporal(nombre_fichero1, "\n\n\n");
	int fd2 = crear_y_escribir_en_fichero_temporal(nombre_fichero2, "12345");
	int fd3 = crear_y_escribir_en_fichero_temporal(nombre_fichero3, "123\n");
	int fd4 = crear_y_escribir_en_fichero_temporal(nombre_fichero4, "1\n3\n567\n");
	int fd5 = crear_y_escribir_en_fichero_temporal(nombre_fichero5, "123456789012\n4567");

	char *linea1, *linea2, *linea3, *linea4, *linea5, *linea6, *linea7, *linea8, *linea9, *linea10, *linea11, *linea12, *linea13, *linea14, *linea15;
	assertEqualString((linea1 = get_next_line(fd1)), "\n");
	assertEqualString((linea2 = get_next_line(fd1)), "\n");
	assertEqualString((linea3 = get_next_line(fd2)), "12345");
	assertEqualString((linea4 = get_next_line(fd1)), "\n");
	assertEqualString((linea5 = get_next_line(fd2)), NULL);
	assertEqualString((linea6 = get_next_line(fd3)), "123\n");
	assertEqualString((linea7 = get_next_line(fd3)), NULL);
	assertEqualString((linea8 = get_next_line(fd1)), NULL);
	assertEqualString((linea9 = get_next_line(fd4)), "1\n");
	assertEqualString((linea10 = get_next_line(fd5)), "123456789012\n");
	assertEqualString((linea11 = get_next_line(fd4)), "3\n");
	assertEqualString((linea12 = get_next_line(fd5)), "4567");
	assertEqualString((linea13 = get_next_line(fd4)), "567\n");
	assertEqualString((linea14 = get_next_line(fd5)), NULL);
	assertEqualString((linea15 = get_next_line(fd4)), NULL);

	free(linea1);
	free(linea2);
	free(linea3);
	free(linea4);
	free(linea5);
	free(linea6);
	free(linea7);
	free(linea8);
	free(linea9);
	free(linea10);
	free(linea11);
	free(linea12);
	free(linea13);
	free(linea14);
	free(linea15);

	unlink(nombre_fichero1);
	unlink(nombre_fichero2);
	unlink(nombre_fichero3);
	unlink(nombre_fichero4);
	unlink(nombre_fichero5);
	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);
	close(fd5);
}


int main()
{
	printf(TITULO("TEST1:")"\n");
	test1();

	return (0);
}
