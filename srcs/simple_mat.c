#include "minishell.h"

int nb_erase(char **tmp, char try)
{
	int nb_erase;
	int x;

	nb_erase = 0;
	x = 0;
	while (1)
	{
		if (x >= ft_matrixlen(tmp))
			break ;
		tmp = &tmp[x];
		x = find_next_char(tmp, try);
		x++;
		nb_erase++;
	}
	return (nb_erase);
}

char *cpy_with_malloc(char *tmp)
{
	char *out;

	out = malloc(sizeof(char) * ft_strlen(tmp) + 1);
	if (!out)
		return (NULL);
	ft_strlcpy(out, tmp, ft_strlen(tmp));
	return (out);
}

void ft_clean_mat(char **mat)
{
	int x;

	x = ft_matrixlen(mat);
	while (--x > -1)
		free(mat[x]);
	free(mat);
}

char **simple_mat(char **start_mat)
{
	char **final_mat;
	int y;
	int x;

	final_mat = malloc(sizeof(char *) * ft_matrixlen(start_mat) - \
		((nb_erase(start_mat, '>') + nb_erase(start_mat, '<')) * 2) + 1);
	if (!final_mat)
		return (NULL); //free all
	x = -1;
	y = -1;
	while (++x < ft_matrixlen(start_mat))
	{
		if (x + 1 < ft_matrixlen(start_mat))
		{
			if (start_mat[x][0] == '<' || start_mat[x][0] == '>')
				x++;
			else
				final_mat[++y] = cpy_with_malloc(start_mat[x]);
		}
		else
			final_mat[++y] = cpy_with_malloc(start_mat[x]);
	}
	final_mat[++y] = NULL;
	ft_clean_mat(start_mat);
	return (final_mat);
}
