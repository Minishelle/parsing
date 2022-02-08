#include "minishell.h"


char	*find_in_env(char **envp, char *word, int len_word, int len_return)
{
	char	*path;
	int		i;

	i = -1;
	len_word = 0;
	while (ft_matrixlen(envp) > ++i)
	{
		if (!ft_strncmp(envp[i], word, ft_strchr_up(envp[i], '=')))
		{
			path = ft_calloc(sizeof(char), ft_strlen(envp[i]) + 1);
			ft_strlcpy(path, &envp[i][len_return], ft_strlen(envp[i]) + 1);
			return (path);
		}
	}
	return (NULL);
}
