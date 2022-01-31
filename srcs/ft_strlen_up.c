#include "minishell.h"

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
