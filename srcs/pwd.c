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
	int		fd;

	path = NULL;
	path = getcwd(path, 0);
	fd = ft_open(cmd);
	ft_putstr_fd(path, fd);
	write(fd, "\n", 1);
	free(path);
	path = NULL;
}
