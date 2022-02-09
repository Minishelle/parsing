/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuccher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 16:51:00 by lbuccher          #+#    #+#             */
/*   Updated: 2022/01/12 17:08:52 by lbuccher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**get_path(char *env[])
{
	char	*all_path;
	char	**split_path;

	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
			break ;
		(*env)++;
	}
	all_path = ft_substr(*env, 5, ft_strlen(*env) - 5);
	split_path = ft_split_pipex(all_path, ':');
	free(all_path);
	return (split_path);
}

void	process(char *env[], char **cmd)
{
	int		i;
	char	*tmp;
	char	**paths;
	char	*cmd_path;

	i = -1;
	paths = get_path(env);
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], "/");
		if (ft_strncmp(cmd_path, cmd[0], ft_strlen(cmd_path)) == 0)
			break ;
		tmp = ft_strjoin(cmd_path, cmd[0]);
		free(cmd_path);
		cmd_path = tmp;
		if (!access(cmd_path, F_OK))
			break ;
		if (paths[i + 1])
			free(cmd_path);
	}
	ft_end_process(cmd_path, cmd, paths, env);
}

void pipex_rec(t_datas_cmd *cmds, char *env[], int prev_fd[2], t_one_cmd *cmd)
{
	int next_fd[2];
	pid_t pid;

	if (pipe(next_fd) == -1)
		return (perror("pipe"));
	pid = fork();
	if (pid < 0)
		return (perror("fork"));
	else if (pid == 0)
	{
		if (cmd->type_next == 2)
		{
			close(next_fd[0]);
			if (dup2(next_fd[1], 1) < 0) // dup2(infile, 0)
				return (perror("first: fd"));
			close(next_fd[1]);
			//close_pipe(next_fd);
			//close_pipe(prev_fd);
		}
		else if (cmds->nb_cmds > 1 && cmd->type_next == 0)
		{
			close(prev_fd[1]);
			if (dup2(prev_fd[0], 0) < 0) // dup2(outfile, 1)
				return (perror("last: fd"));
			close(prev_fd[0]);
			//close_pipe(prev_fd);
			//close_pipe(next_fd);
		}
		else if (cmds->nb_cmds > 1 && cmd->type_next != 0)
		{
			close(prev_fd[1]);
			close(next_fd[0]);
			if (dup2(next_fd[1], 1) < 0 || dup2(prev_fd[0], 0) < 0)
				return (perror("middle: fd"));
			close(prev_fd[0]);
			close(next_fd[1]);
		//	close_pipe(prev_fd);
		//	close_pipe(next_fd);
		}
		process(env, cmd->all_cmd);
	}
	else
	{
		close_pipe(prev_fd);
		waitpid(pid, NULL, 0);
		if (cmd->next)
			pipex_rec(cmds, env, next_fd, cmd->next);
		close_pipe(next_fd);
		return ;
	}
}
