/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuccher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 16:51:00 by lbuccher          #+#    #+#             */
/*   Updated: 2022/02/18 15:56:10 by mbucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	process(char *env[], char **cmd, t_one_cmd *cmd_struct, int to_exec)
{
	int		i;
	char	*tmp;
	char	**paths;
	char	*cmd_path;

	i = -1;
	if (ft_strlen(cmd_struct->cmd) > 2 && cmd_struct->cmd[0] == '.'
		&& cmd_struct->cmd[1] == '/' && to_exec)
		ft_end_process(cmd_struct->cmd, cmd_struct->all_cmd, NULL, env, \
				cmd_struct);
	paths = get_path(env);
	if (!paths)
		return ;
	if (!paths && to_exec)
	{
		if (access(cmd_struct->cmd, F_OK) == 0)
		{
			ft_clean_mat(paths);
			execve(cmd_struct->cmd, cmd, env);
		}
		else if (!check_builtin(cmd_struct))
		{
			perror_cnf("command not found: ", cmd[0], 2);
			datas_prompt.last_command_status = 127;
		}
		return ;
	}
	else if (!paths && !to_exec)
		return ;
	while (cmd_struct->cmd && paths && paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], "/");
		if (!cmd_path)
		{
			ft_clean_mat(paths);
			exit (1);
		}
		if (ft_strncmp(cmd_path, cmd[0], ft_strlen(cmd_path)) == 0)
			break ;
		tmp = ft_strjoin(cmd_path, cmd[0]);
		free(cmd_path);
		if (!tmp)
		{
			ft_clean_mat(paths);
			exit (1);
		}
		cmd_path = tmp;
		if (!access(cmd_path, F_OK))
			break ;
		if (paths[i + 1])
			free(cmd_path);
	}
	if (to_exec)
		ft_end_process(cmd_path, cmd, paths, env, cmd_struct);
	if (cmd_path)
		free(cmd_path);
	ft_clean_mat(paths);
}

void	ft_redirection(int fd_in, int fd_out, int simple, int first, t_one_cmd *cmd)
{
	(void)cmd;
	if (simple == 1 && first == 1)
	{
		close(fd_in);
		if (dup2(fd_out, 1) < 0)
			return (perror("first: fd"));
		close(fd_out);
	}
	else if (simple == 1 && first == 0)
	{
		close(fd_out);
		if (dup2(fd_in, 0) < 0)
			return (perror("last: fd"));
		close(fd_in);
	}
	else
	{
		if (dup2(fd_out, 1) < 0 || dup2(fd_in, 0) < 0)
			return (perror("middle: fd"));
		close(fd_out);
		close(fd_in);
	}
}

void	multi_pipe(t_datas_cmd *cmds, int n_fd[2], int pr_fd[2], t_one_cmd *cmd)
{
	if (cmd->type_next == 2)
	{
		if (cmd->infile == 0)
			ft_redirection(n_fd[0], n_fd[1], 1, 1, cmd);
		else
			ft_redirection(cmd->infile, n_fd[1], 0, 1, cmd);
	}
	else if (cmds->nb_cmds > 1 && cmd->type_next != 0)
	{
		close(pr_fd[1]);
		close(n_fd[0]);
		ft_redirection(pr_fd[0], n_fd[1], 0, 0, cmd);
	}
	else if (cmds->nb_cmds > 1 && cmd->type_next == 0)
	{
		if (cmd->outfile == 1)
			ft_redirection(pr_fd[0], pr_fd[1], 1, 0, cmd);
		else
		{
			close(pr_fd[1]);
			ft_redirection(pr_fd[0], cmd->outfile, 0, 0, cmd);
		}
	}
}

void	minishell_cmd(char **env, t_one_cmd *cmd)
{
	char **cmd_shell;

	cmd_shell = malloc(2 * sizeof(char *));
	cmd_shell[0] = cmd->cmd;
	cmd_shell[1] = "\n";
	execve(*cmd_shell, cmd_shell, env);
}

static void i_find_a_signal(int this_signal)
{
	if (this_signal == SIGQUIT)
	{
		ft_putstr_fd("QUIT: 3", 1);
		kill(datas_prompt.pid, SIGKILL);
		datas_prompt.last_command_status = 131;
	}
	else
		datas_prompt.last_command_status = 130;
	ft_putstr_fd("\n", 1);
}

void	pipe_rec(t_datas_cmd *cmds, char **env, int pre_fd[2], t_one_cmd *cmd)
{
	int		next_fd[2];
	pid_t	pid;
	int tmp;

	/*if (cmd->cmd && !ft_strncmp("./", cmd->cmd, 2))
		minishell_cmd(env, cmd);*/
	if (!ft_strlen(cmd->cmd) || ft_strncmp(cmd->cmd, "exit",  4))
	{
		if (pipe(next_fd) == -1)
			return (perror("pipe"));
		pid = fork();
		datas_prompt.pid = pid;
		if (pid < 0)
			return (perror("fork"));

		if (pid == 0)
		{
			if (cmds->nb_cmds == 1)
			{
				if (dup2(cmd->outfile, 1) < 0 || dup2(cmd->infile, 0) < 0)
					return (perror("one cmd: fd"));
			}
			else
				multi_pipe(cmds, next_fd, pre_fd, cmd);
			if (!check_builtin(cmd))
				process(env, cmd->all_cmd, cmd, 1);
			else
			{
				find_builtin(cmd);
				process(env, cmd->all_cmd, cmd, 0);
				exit(0);
			}
		}
		else
		{
			signal(SIGINT, i_find_a_signal);
			signal(SIGQUIT, i_find_a_signal);
			close_pipe(pre_fd);
			waitpid(pid, &tmp, 0);
			if ((datas_prompt.last_command_status != 130 && datas_prompt.last_command_status != 131) && datas_prompt.last_command_status)
				datas_prompt.last_command_status = tmp / 255;
			if (cmd->cmd)
				find_builtin_env(cmd);
			if (cmd->next)
				pipe_rec(cmds, env, next_fd, cmd->next);
			else
				process(env, cmd->all_cmd, cmd, 0);
			close_pipe(next_fd);
		}
	}
	else
		ft_exit();
}
