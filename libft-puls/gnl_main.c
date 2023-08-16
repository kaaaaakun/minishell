#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "get_next_line.h"
#include "get_next_line_bonus.h"

__attribute__((destructor))
static void destructor() {
    system("leaks -q a.out");
}

int	main(void)
{
	int i = 0;
	int fd = 0;//open("a.txt",O_RDONLY);
	while(i++ < 10)
	{
		char *line = get_next_line(fd);
		printf ("%d:%s",i,line);
		free(line);
	}
	return (0);
}

void *mymalloc(size_t size)
{
	size = 0;
	return (NULL);
}
