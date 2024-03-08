#include <fcntl.h>		// open
#include <string.h>		// strerror
#include <sys/errno.h>		// errno
#include <stdio.h>		// printf
#include <unistd.h>		// close
#include "get_next_line.h"


void mostrar_error(char *motivoError)
{
	printf("Error %s: %d\n", motivoError, errno);
	printf("%s\n", strerror(errno));
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Debe especificar un archivo a abrir.\n");
		return (0);
	}

	int fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		mostrar_error("al intentar abrir el archivo");
		return (-1);
	}

	int i = close(0);
	if (i == -1)
	{
		mostrar_error("al cerrar el archivo");
		return (-1);
	}
}

