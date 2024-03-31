#include <fcntl.h>		// open, O_RDONLY
#include <stdio.h>		// printf
#include <string.h>		// strerror
#include <sys/errno.h>	// errno
#include <unistd.h>		// close
#include "get_next_line.h"


void mostrar_error(char *accionError)
{
	printf("Se ha producido un error %s.\n", accionError);
	printf("Código del error: %d\n", errno);
	printf("Mensaje de error: \"%s\"\n", strerror(errno));
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Debe especificar un archivo de texto a abrir.\n");
		return (-1);
	}

	int fd;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		mostrar_error("al intentar abrir el archivo");
		return (-1);
	}

	int num_lineas = 0;
	char *next_line;
	while ((next_line = get_next_line(fd)) != NULL)
	{
		printf("Línea %d: %s", num_lineas + 1, next_line);
		if (strchr(next_line, '\n') == NULL)
			printf("\n");
		num_lineas++;
		free(next_line);
	}
	printf("%d línea(s) procesada(s).\n", num_lineas);

	// Desmarcar para forzar un error en el [segundo] close:
	//     close(fd);
	if (close(fd) == -1)
	{
		mostrar_error("al cerrar el archivo");
		return (-1);
	}
}
