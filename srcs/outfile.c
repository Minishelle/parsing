#include "minishell.h"

int open_fd(char *cmd, int stat)
{
	char *str;
	int fd;

	str = NULL;
	fd = 0;
	if (stat)
		fd = open(cmd, O_CREAT | O_RDWR, 0644);
	else
		fd = open(cmd, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd <= 0)
	{
		write(2, "Wrong filename\n", 15);
		exit (1); //free all
	}
	if (stat)
	{
		while (read(fd, str, 1000) != -1)
			free(str);
		if (str)
			free(str);
	}
	return (fd);
}

int give_me_fd(char **all_cmd, int x)
{
	if (ft_strlen(all_cmd[x - 1]) > 1)
	{
		if (all_cmd[x - 1][1] == '>')
			return (open_fd(all_cmd[x], 1));
		else
		{
			write(2, "Wrong operator\n", 15);
			exit (1); //free all
		}
	}
	else
		return (open_fd(all_cmd[x], 0));
	return (1);
}

int outfile(char **all_cmd)
{
	int x;
	int fd;

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
		fd = give_me_fd(all_cmd, x);
	}
	return (fd);
}
