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

int ft_strlen_up(char *str, char *search)
{
	int x;
	int y;
	int output;

	y = -1;
	output = ft_strlen(str);
	while (search[++y])
	{
		x = 0;
		while (str[x] && str[x] != search[y])
			x++;
		if (output > x)
			output = x;
	}
	return (output);
}

char **modif_mat(char **cmds, char **envp)
{
	int x;
	int y;
	int size;
	char *tmp1;
	char *tmp2;
	char *tmp3;

	x = -1;
	while(++x < ft_matrixlen(cmds))
	{
		y = -1;
		while (++y < (int)ft_strlen(cmds[x]))
		{
			if (cmds[x][y] == '$')
			{
				if ((y > 0 && cmds[x][0] == '"') || (y == 0))
				{
					size = ft_strlen_up(&cmds[x][y + 1], " \"");
					tmp1 = find_in_env(envp, &cmds[x][y + 1], size, size + 1);
					tmp2 = ft_calloc(sizeof(char), y);
					ft_strlcpy(tmp2, cmds[x], y);
					tmp3 = ft_strjoin(tmp2, tmp1);
					free(tmp2);
					tmp1 = ft_calloc(sizeof(char), ft_strlen(&cmds[x][y + ft_strlen_up(&cmds[x][y + 1], " \"")]));
					ft_strlcpy(tmp1, &cmds[x][y + 1+ ft_strlen_up(&cmds[x][y + 1], " \"")], ft_strlen(&cmds[x][y + ft_strlen_up(&cmds[x][y + 1], " \"")]));
					tmp2 = ft_strjoin(tmp3, tmp1);
					free(tmp1);
					free(tmp3);
					free(cmds[x]);
					cmds[x] = tmp2;
				}
			}
		}
	}
	return (cmds);
}

t_one_cmd	*trans_cmd(char **cmds, char **envp)
{
	int			x;
	t_one_cmd	*cmd;

	cmds = pipen_t(cmds);
	if (!cmds)
		return (NULL);
	cmd = malloc(sizeof(t_one_cmd));
	if (!cmd)
		exit(0); //free
	cmd->all_cmd = ft_matrixlcpy(cmds, find_next_char(cmds, '|'));
	cmd->all_cmd = modif_mat(cmd->all_cmd, envp);
	cmd->infile = 0;
	cmd->outfile = 1;
	cmd->cmd = cmd->all_cmd[0];
	x = find_next_char(cmds, '|');
	cmd->type_next = 0;
	cmd->next = NULL;
	if (x != ft_matrixlen(cmds))
	{
		if (cmds[x][0] == '|')
			cmd->type_next = 1;
		else
			cmd->type_next = 2;
		cmd->next = trans_cmd(&(cmds[x + 1]), envp);
	}
	return(cmd);
}
