#include <fcntl.h>		// open, O_RDONLY
#include "assertions.h"
#include "get_next_line.h"

void test1()
{
	int fd = open("1.txt", O_RDONLY);

	assertEqualString(get_next_line(fd), "123");
	assertEqualString(get_next_line(fd), NULL);

	close(fd);
}

int main()
{
	printf("TEST1\n");
	test1();

	return (0);
}
