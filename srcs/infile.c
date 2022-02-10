/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoorick <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 18:34:26 by hgoorick          #+#    #+#             */
/*   Updated: 2022/02/10 18:34:38 by hgoorick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/****************************************
*
*	Nom : infile
*	Params : matrice reprenant toute la commande
*	Retour : le fd du infile
*	Descritpion:
*		Cherche une redirection pour le infile, si il le trouve, il open le file
* 			donne si il ne trouve pas de redirection le infile est a 0
*
****************************************/

int	infile(char **all_cmd)
{
	int	x;
	int	fd;

	x = 0;
	fd = 0;
	while (1)
	{
		if (fd > 1)
			all_cmd = &all_cmd[x];
		x = find_next_char(all_cmd, '<');
		if (x == ft_matrixlen(all_cmd))
			break ;
		else if (fd > 1)
			close(fd);
		if (x == ft_matrixlen(all_cmd) - 1)
			exit (0); //free all
		x+=2;
		fd = open(all_cmd[x - 1], O_RDONLY);
		if (fd <= 0)
		{
			write(1, "Wrong filename\n", 15);
			exit (0); //free all
		}
	}
	return (fd);
}
