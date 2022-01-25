#include "libft.h"

int ft_isspace(char c)
{
	if (c == '\t')
		return (1);
	else if (c == ' ')
		return (1);
	return (0);
}
