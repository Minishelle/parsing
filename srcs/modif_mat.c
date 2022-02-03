#include "minishell.h"

char *return_char(char **cmds, int x, int y, char **envp)
{
	int size;
	char *tmp1;
	char *tmp2;
	char *tmp3;

	size = ft_strlen_up(&cmds[x][y + 1], " \"");
	tmp1 = find_in_env(envp, &cmds[x][y + 1], size, size + 1);
	tmp2 = ft_calloc(sizeof(char), y);
	ft_strlcpy(tmp2, cmds[x], y);
	tmp3 = ft_strjoin(tmp2, tmp1);
	free(tmp2);
	free(tmp1);
	tmp1 = ft_calloc(sizeof(char), ft_strlen(&cmds[x][y + ft_strlen_up(&cmds[x][y + 1], " \"")]));
	ft_strlcpy(tmp1, &cmds[x][y + 1+ ft_strlen_up(&cmds[x][y + 1], " \"")], ft_strlen(&cmds[x][y + ft_strlen_up(&cmds[x][y + 1], " \"")]));
	tmp2 = ft_strjoin(tmp3, tmp1);
	free(tmp1);
	free(tmp3);
	free(cmds[x]);
	return (tmp2);
}
char **modif_mat(char **cmds, char **envp)
{
	int x;
	int y;

	x = -1;
	while(++x < ft_matrixlen(cmds))
	{
		y = -1;
		while (++y < (int)ft_strlen(cmds[x]))
			if (cmds[x][y] == '$')
				if ((y > 0 && cmds[x][0] == '"') || (y == 0))
					cmds[x] = return_char(cmds, x, y, envp);
	}
	return (cmds);
}
