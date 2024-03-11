#include <fcntl.h>		// open, O_RDONLY
#include "get_next_line.h"
#include "assertions.h"

void test1()
{
	int fd = open("1.txt", O_RDONLY);

	assertEqualString(get_next_line(fd), "12345");
	assertEqualString(get_next_line(fd), NULL);

	close(fd);
}

void test2()
{
	int fd = open("2.txt", O_RDONLY);

	assertEqualString(get_next_line(fd), "123");
	assertEqualString(get_next_line(fd), NULL);

	close(fd);
}

int main()
{
	printf("TEST1:\n");
	test1();

	printf("TEST2:\n");
	test2();

	return (0);
}
