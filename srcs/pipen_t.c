#include "minishell.h"

char **pipen_t(char **cmds)
{
	while (!find_next_char(cmds, '|'))
	{
		if (ft_matrixlen(cmds) > 1)
			cmds = &cmds[1];
		else
			return (NULL);
	}
	return (cmds);
}
