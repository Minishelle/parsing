/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_mat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoorick <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 18:10:53 by hgoorick          #+#    #+#             */
/*   Updated: 2022/02/10 18:10:57 by hgoorick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/****************************************
*
*	Nom : find_in_struct
*	Params : - Liste de char recherchee a travers toute la liste chainee
*			 - Pointeur vers la premiere strcut de la liste chainee
*	Retour : La liste de char liee a la lste de char recherchee
*	Descritpion:
*		Compare la liste de chars recherchee a celle de la struct, si elles sont
*			egales alors on retourne une copie de la liste de char liee sinon on
*			refait la fonction sur la strcut suivante de la liste chainee, si il
*			n'y en a pas alors le code renvoi nul
*
****************************************/

char	*find_in_struct(char *var_env, t_var_env *out)
{
	char	*tmp1;

	if (!out)
		return (NULL);
	if (!ft_strncmp(var_env, out->name_var, ft_strlen(out->name_var)))
	{
		tmp1 = ft_calloc(sizeof(char), ft_strlen(out->var_txt));
		if (!tmp1)
			return (NULL);
		ft_strlcpy(tmp1, out->var_txt, ft_strlen(out->var_txt));
		return (tmp1);
	}
	else if (out->next)
		return (find_in_struct(var_env, out->next));
	return (NULL);
}

/****************************************
*
*	Nom : ft_free_little_matrice
*	Params : - Matrice de 3 liste de char
*			 - L'index qui ne doit pas etre free
*	Retour : Void
*	Descritpion:
*		Free les trois index de la matrice sauf si le nombre donne est compris
*			entre 0 et 2, dans ce cas l'index egal au nombre ne sera pas free
*
****************************************/

void	ft_free_little_matrice(char **mat, int x)
{
	int	y;

	y = -1;
	while (++y < 3)
		if (y != x)
			free(mat[y]);
}

/****************************************
*
*	Nom : return_char
*	Params : - liste de chars liee a la Matrice de la commande
*			 - la positon dans la liste de chars
*			 - la matrice d'env
*			 - la premiere stuct de la liste chainee
*	Retour : Liste de char modifie ou on remplace la var d'env par sa liste de
*				char liee
*	Descritpion:
*		Defini la longueur de la var d'env, prend ensuite la liste de char liee
*			a la var d'env, cut avant et apres la variable d'env et colle les
*			deux partie avec la liste de char liee a la var d'env
*
****************************************/

char	*return_char(char *cmds, int y, char **envp, t_var_env *out_struct)
{
	int		size;
	char	**tmp;
	char	*tmp_out;

	size = ft_strlen_up(&cmds[y + 1], " \"");
	tmp = malloc(sizeof(char *) * 3);
	if (!tmp)
		exit (0);
	tmp[0] = find_in_env(envp, &cmds[y + 1], size, size + 1);
	if (tmp[0] == NULL)
	{
		tmp[0] = find_in_struct(&cmds[y + 1], out_struct);
		if (tmp[0] == NULL)
		{
			tmp[0] = malloc(sizeof(char) * 2);
			if (!tmp[0])
			{
				free(tmp);
				return (NULL);
			}
			tmp[0][0] = '\0';
		}
	}
	tmp[1] = ft_calloc(sizeof(char), y);
	if (!tmp[1])
	{
		if (tmp[0])
		{
			free(tmp[0]);
			free(tmp);
		}
		return (NULL);
	}
	ft_strlcpy(tmp[1], cmds, y);
	tmp[2] = ft_strjoin(tmp[1], tmp[0]);
	if (!tmp[2])
	{
		ft_free_little_matrice(tmp, 2);
		return (NULL);
	}
	ft_free_little_matrice(tmp, 2);
	tmp[0] = ft_calloc(sizeof(char), ft_strlen(&cmds[y + \
		ft_strlen_up(&cmds[y + 1], " \"")]));
	if (!tmp[0])
	{
		ft_free_little_matrice(tmp, 0);
		return (NULL);
	}
	ft_strlcpy(tmp[0], &cmds[y + 1 + ft_strlen_up(&cmds[y + 1], " \"")], \
		ft_strlen(&cmds[y + ft_strlen_up(&cmds[y + 1], " \"")]));
	tmp[1] = ft_strjoin(tmp[2], tmp[0]);
	if (!tmp[1])
	{
		ft_free_little_matrice(tmp, 1);
		return (NULL);
	}
	ft_free_little_matrice(tmp, 1);
	if (cmds)
		free(cmds);
	tmp_out = cpy_with_malloc(tmp[1]);
	free(tmp[1]);
	free(tmp);
	return (tmp_out);
}

/****************************************
*
*	Nom : modif_mat
*	Params : - La Matrice de la commande
*			 - la matrice d'env
*			 - la premiere stuct de la liste chainee
*	Retour : La Matrice de la commande ou les vars d'env ont ete remplacees par
*				leurs valeurs
*	Descritpion:
*		Parcour la liste puor trouver un $ signifiant qu'il a trouve une var
*			d'env, la commande return char var s'occuper de remplacer la var
*			d'env par sa valeur reelle
*
****************************************/

char	*modif_mat2(char *cmd, int y, char **envp, t_var_env *out_struct)
{
	char	*tmp;
	char	*tmp1;
	if (cmd[y] == '$')
	{
		if (y <= (int)ft_strlen(cmd) - 1 && cmd[y + 1] == '?')
		{
			tmp1 = ft_itoa(datas_prompt.last_command_status);
			tmp = ft_calloc(ft_strlen(cmd) - 2 + ft_strlen(tmp1), \
				sizeof(char));
			ft_strlcpy(tmp, cmd, y);
			ft_strlcpy(&tmp[y], tmp1, ft_strlen(tmp1) + 1);
			ft_strlcpy(&tmp[y + ft_strlen(tmp1)], &cmd[y + 2], \
				ft_strlen(&cmd[y + 2]) + 1);
			free(cmd);
			cmd = tmp;
		}
		else if ((y > 0 && cmd[0] == '"') || (y == 0))
			cmd = return_char(cmd, y, envp, out_struct);
	}
	return (cmd);
}

char	*replace_two_char(char *cmd, char erase)
{
	int x;
	int y;
	int count;
	char *return_char;

	x = -1;
	y = -1;
	return_char = malloc(sizeof(char) * ft_strlen(cmd) - 1);
	if (!return_char)
		return (NULL);
	count = 0;
	while (++x < (int)ft_strlen(cmd) && count != 2)
	{
		if (cmd[x] != erase)
			return_char[++y] = cmd[x];
		else
			count++;
	}
	--x;
	while (++x < (int)ft_strlen(cmd))
		return_char[++y] = cmd[x];
	return_char[++y] = '\0';
	free(cmd);
	return (return_char);
}

char	**modif_mat(char **cmds, char **envp, t_var_env *out_struct)
{
	int		x;
	int		y;
	int		stat_simple;
	int stat_double;

	x = -1;
	while (++x < ft_matrixlen(cmds))
	{
		y = -1;
		stat_simple = 0;
		stat_double = 0;
		while (++y < (int)ft_strlen(cmds[x]))
		{
			cmds[x] = modif_mat2(cmds[x], y, envp, out_struct);
			if (cmds[x][y] == '"' && !stat_simple)
			{
				stat_double++;
				if (!(stat_double % 2))
				{
					cmds[x] = replace_two_char(cmds[x], '"');
					stat_double = 0;
					y-=2;
				}
			}
			else if (cmds[x][y] == 39 && !stat_double)
			{
				stat_simple++;
				if (!(stat_simple % 2))
				{
					cmds[x] = replace_two_char(cmds[x], 39);
					stat_simple = 0;
					y-=2;
				}
			}
		}
	}
	return (cmds);
}
