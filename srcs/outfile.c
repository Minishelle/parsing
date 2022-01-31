#include "minishell.h"

int outfile(char **all_cmd)
{
	int x;
	int fd;

	x = 0;
	fd = 1;
	while (1)
	{
		if (fd > 1)
			all_cmd = &all_cmd[x];
		x = find_next_char(all_cmd, '>');
		if (x == ft_matrixlen(all_cmd))
			break ;
		else if (fd > 1)
			close(fd);
		if (x == ft_matrixlen(all_cmd) - 1 || x == 0)
			exit (0); //free all
		x++;
		fd = open(all_cmd[x], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd <= 0)
		{
			write(2, "Wrong filename\n", 15);
			exit (1); //free all
		}
	}
	return (fd);
}
