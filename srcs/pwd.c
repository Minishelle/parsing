/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:22:12 by mbucci            #+#    #+#             */
/*   Updated: 2022/02/15 12:54:16 by mbucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_one_cmd *cmd)
{
	char	*path;

	(void) cmd;
	path = NULL;
	path = getcwd(path, 0);
	ft_putstr_fd(path, 1);
	write(1, "\n", 1);
	free(path);
	path = NULL;
}
