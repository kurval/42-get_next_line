#include <stdio.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/types.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
	int fd;
	int ret;
	char *buff;
	int line;

	line = 0;
	if (argc  ==  2)
	{
		fd = open(argv[1], O_RDONLY);
		while ((ret = get_next_line(fd, &buff)) > 0)
		{
			printf("Return value: %d: %d Line #%d: %s\n", fd, ret, ++line, buff);
			free(buff);
		}
		printf("Return value: %d: %d Line #%d: %s\n", fd, ret, ++line, buff);
		if (ret == -1)
			printf("***********\nERROR\n");
		else if (ret == 0)
			printf("***********\nEND OF FILE\n");
		close(fd);
	}
	if (argc == 1)
	{
		while ((ret = get_next_line(0, &buff)) > 0)
			printf("Return value: %d Line #%d: %s\n", ret, ++line, buff);
		if (ret == -1)
			printf("************\nERROR\n");
		else if (ret == 0)
			printf("************\nEND OF STDIN\n");
		close(fd);
	}
	return (0);
}
