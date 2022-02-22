/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuccher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:07:00 by lbuccher          #+#    #+#             */
/*   Updated: 2022/02/16 12:07:03 by lbuccher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_here_doc2(t_datas_cmd *cmds, char *here_doc, char *join, int here_fd)
{
	char	*tmp;
	char **tmp1;


	tmp1 = ft_split(join, '\n');
	int x = -1;
	while (++x < (ft_matrixlen(tmp1) + 1) - cmds->type_hd)
	{
		if (!x)
			tmp = cpy_with_malloc(tmp1[x]);
		else
			tmp = ft_strjoin_up(tmp, tmp1[x]);
	}
	ft_clean_mat(tmp1);
	ft_putstr_fd(join, here_fd);
	close(here_fd);
	here_fd = open("tmp", O_RDONLY, 0644);
	free(here_doc);
	if (cmds->nb_cmds && cmds->cmd_first->cmd)
		cmds->cmd_first->infile = here_fd;
	else
	{
		read(here_fd, tmp, ft_strlen(join));
		ft_putstr_fd(tmp, 1);
		close(here_fd);
	}
	free(join);
	free(tmp);
	/*tmp = malloc((ft_strlen(join) * sizeof(char)) + 1);
	write(here_fd, join, ft_strlen(join));
	close(here_fd);
	here_fd = open("tmp", O_RDONLY, 0644);
	free(here_doc);
	if (cmds->nb_cmds && cmds->cmd_first->cmd)
		cmds->cmd_first->infile = here_fd;
	else
	{
		read(here_fd, tmp, ft_strlen(join));
		write(1, tmp, ft_strlen(tmp));
		close(here_fd);
	}
	free(join);
	free(tmp);*/
}

void	ft_here_doc(t_datas_cmd *cmds, char **end_word)
{
	char	*here_doc;
	char	*join;
	int		here_fd;
	int		i;

	join = malloc(1);
	here_fd = open("tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	i = 0;
	if (here_fd == -1)
		return (perror("open"));
	while (1)
	{
		ft_putstr_fd("heredoc>", 1);
		here_doc = get_next_line(0);
		if (here_doc && (ft_strlen(end_word[i]) == ft_strlen(here_doc) - 1)
			&& !ft_strncmp(here_doc, end_word[i], ft_strlen(end_word[i])))
				i++;
		else
			i = 0;
		if (i == cmds->type_hd)
			break ;
		join = ft_strjoin_up(join, here_doc);
		free(here_doc);
	}
	ft_here_doc2(cmds, here_doc, join, here_fd);
}
