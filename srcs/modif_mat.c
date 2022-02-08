#include "minishell.h"

char *find_in_struct(char *var_env, t_var_env *out_struct)
{
	if (!out_struct)
		return (NULL);
	if (!ft_strncmp(var_env, out_struct->name_var, ft_strlen(out_struct->name_var)))
		return (out_struct->var_txt);
	else if (out_struct->next)
		return (find_in_struct(var_env, out_struct->next));
	return (NULL);
//parcourir la listre chainee pour trouver var env et return sa value else return null
}

char *return_char(char **cmds, int x, int y, char **envp, t_var_env *out_struct)
{
	int size;
	char *tmp1;
	char *tmp2;
	char *tmp3;

	size = ft_strlen_up(&cmds[x][y + 1], " \"");
	tmp1 = find_in_env(envp, &cmds[x][y + 1], size, size + 1);
	if (tmp1 == NULL)
	{
		tmp1 = find_in_struct(&cmds[x][y + 1], out_struct);
		if (tmp1 == NULL)
		{
			tmp1 = malloc(sizeof(char) * 2);
			tmp1[0] = '\0';
			return (tmp1);
		}
		else
			return (tmp1);
	}
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
char **modif_mat(char **cmds, char **envp, t_var_env *out_struct)
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
					cmds[x] = return_char(cmds, x, y, envp, out_struct);
	}
	return (cmds);
}
