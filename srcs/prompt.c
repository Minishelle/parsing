#include "minishell.h"

char	*start_prompt(char **env)
{
	char	*output;
	char	*tmp;
	char	*tmp1;

	tmp = find_in_env(env, "USER=", 5, 5);
	tmp1 = ft_strjoin("\033[0;91m", tmp);
	output = ft_strjoin(tmp1, "\033[0;39m@\033[0;92mminishell\033[0;39m > ");
	free(tmp);
	free(tmp1);
	return (output);
}
