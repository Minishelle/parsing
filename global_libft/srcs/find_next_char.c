#include "libft.h"

int	find_next_char(char **all_cmds, char c)
{
	int	x;

	x = -1;
	while (++x < ft_matrixlen(all_cmds))
		if (all_cmds[x][0] == c)
			break ;
	return (x);
}
