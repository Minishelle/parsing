/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:49:11 by mbucci            #+#    #+#             */
/*   Updated: 2022/02/25 18:10:54 by mbucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env(char **tab)
{
	char	*t;
	int		x;
	int		i;
	int		j;

	x = ft_matrixlen(tab);
	i = -1;
	while (++i < x)
	{
		j = i;
		while (++j < x)
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
			{
				t = tab[i];
				tab[i] = tab[j];
				tab[j] = t;
			}
		}
	}
}

void	format_print(char *s)
{
	int	f;

	f = ft_strchr_up(s, '=');
	if (!f)
		f = ft_strlen(s) - 1;
	ft_putstr_fd("declare -x ", 1);
	write(1, s, f + 1);
	if (!ft_strchr_up(s, '='))
		ft_putchar_fd('\n', 1);
	else
	{
		write(1, "\"", 1);
		s = ft_strchr(s, '=');
		if (s++)
			write(1, s, ft_strlen(s));
		ft_putendl_fd("\"", 1);
	}
}

void	export_print(char **tab)
{
	int	i;

	sort_env(tab);
	i = -1;
	while (tab[++i])
		format_print(tab[i]);
}

void	ft_move_link(char *s, t_var_env **src, t_var_env *dst)
{
	t_var_env	*tmp;

	if (!ft_strcmp((*src)->name_var, s))
	{
		while (dst && dst->next)
			dst = dst->next;
		dst->next = *src;
		*src = (*src)->next;
		return ;
	}
	tmp = *src;
	while (tmp && tmp->next && ft_strcmp(s, tmp->next->name_var))
		tmp = tmp->next;
	while (dst && dst->next)
		dst = dst->next;
	dst->next = tmp->next;
	tmp->next = tmp->next->next;
	dst->next->next = NULL;
}

int	redefine_text(t_var_env *ptr, char *s, char *name)
{
	if (ptr->var_txt)
		free(ptr->var_txt);
	ptr->var_txt = ft_substr(s, ft_strlen(name) + 1, ft_strlen(s) - ft_strlen(name) + 1);
	if (!ptr->var_txt)
		return (1);
	return (0);
}

int	add_to_env(char *s)
{
	char		*s_name;
	t_var_env	*tmp1;
	t_var_env	*tmp2;
	t_var_env	*ptr;

	if (!ft_strchr(s, '='))
	{
		if (ft_find_in_list(s, datas_prompt.env_in_struct))
			return (0);
		else if (ft_find_in_list(s, datas_prompt.out_struct))
			ft_move_link(s, &datas_prompt.out_struct, datas_prompt.env_in_struct);
		else
		{
			ptr = (t_var_env *)malloc(sizeof(t_var_env));
			if (!ptr)
				return (1);
			ptr->next = datas_prompt.env_in_struct;
			datas_prompt.env_in_struct = ptr;
			ptr->name_var = ft_strdup(s);
			ptr->var_txt = NULL;
		}
	}
	else
	{
		s_name = ft_substr(s, 0, ft_strchr_up(s, '='));
		if (!s_name)
			return (1);
		tmp1 = ft_find_in_list(s_name, datas_prompt.env_in_struct);
		tmp2 = ft_find_in_list(s_name, datas_prompt.out_struct);
		if (!tmp1 && !tmp2)
			datas_prompt.env_in_struct = ft_new_var_env(s, datas_prompt.env_in_struct);
		else if (tmp1)
		{
			if (redefine_text(tmp1, s, s_name))
				return (1);
		}
		else if (tmp2)
		{
			if (redefine_text(tmp2, s, s_name))
				return (1);
			ft_move_link(s_name, &datas_prompt.out_struct, datas_prompt.env_in_struct);
		}
		free(s_name);
	}
	return (0);
}

void	export(int ac, char **av)
{
	int	i;
	int	status;

	status = 0;
	if (ac == 1)
		export_print(datas_prompt.envp);
	else
	{
		i = 0;
		status = 0;
		while (++i < ac)
		{
			if (check_char_in_name("export", av[i], &status))
				continue ;
			add_to_env(av[i]);
		}
	}
	ft_clean_mat(datas_prompt.envp);
	datas_prompt.envp = conv_env_to_mat();
	datas_prompt.last_command_status = status;
}

int	find_builtin_env(t_one_cmd *cmd)
{
	if (!ft_strncmp("cd", cmd->cmd, 2))
		cd(ft_matrixlen(cmd->all_cmd), cmd->all_cmd);
	else if (!ft_strncmp("export", cmd->cmd, 6))
		export(ft_matrixlen(cmd->all_cmd), cmd->all_cmd);
	else if (!ft_strncmp("unset", cmd->cmd, 5))
		unset(ft_matrixlen(cmd->all_cmd), cmd->all_cmd);
	else
		return (1);
	return (0);
}

int	find_builtin(t_one_cmd *cmd)
{
	if (!ft_strncmp("echo", cmd->cmd, 4))
		echo(ft_matrixlen(cmd->all_cmd), cmd->all_cmd);
	else if (!ft_strncmp("env", cmd->cmd, 3))
		env();
	else if (!ft_strncmp("pwd", cmd->cmd, 3))
		pwd();
	else if (!ft_strncmp("exit", cmd->cmd, 4))
		ft_exit();
	else
		return (1);
	return (0);
}

int	check_builtin(t_one_cmd *cmd)
{
	return ((!ft_strncmp("cd", cmd->cmd, 2))
		|| (!ft_strncmp("echo", cmd->cmd, 4))
		|| (!ft_strncmp("env", cmd->cmd, 3))
		|| (!ft_strncmp("pwd", cmd->cmd, 3))
		|| (!ft_strncmp("export", cmd->cmd, 6))
		|| (!ft_strncmp("unset", cmd->cmd, 5))
		|| (!ft_strncmp("exit", cmd->cmd, 4)));
}

int    ft_exit_all(void)
{
    char **tmp;
    int i;

    tmp = datas_prompt.cmds->cmd_first->all_cmd;
    if (ft_matrixlen(tmp) > 1)
    {
        i = -1;
        while (ft_isdigit(tmp[1][++i]))
            ;
        if (!ft_isdigit(tmp[1][i]) && i != (int)ft_strlen(tmp[1]))
        {
            ft_putstr_fd("Minishell: exit: ", 1);
            ft_putstr_fd(tmp[1], 1);
            ft_putstr_fd(": numeric argument required\n", 1);
            return (255);
        }
        else if (ft_atoi(tmp[1]) && ft_matrixlen(tmp) > 2)
        {
            ft_putstr_fd("bash: exit: too many arguments\n", 1);
            return (1);
        }
        return (ft_atoi(tmp[1]) % 255);
    }
    return (0);
}

void    ft_exit(void)
{
    //char    **tmp;
    int val_return;

    /*tmp = malloc(sizeof(char *) * 3);
     if (tmp)
     {
     tmp[0] = "rm";
     tmp[1] = "-f";
     tmp[2] = "tmp";
     execve("/bin/rm", tmp, datas_prompt.envp);
     free(tmp);
     }*/
    ft_putstr_fd("exit\n", 1);
    val_return = ft_exit_all();
    ft_free_datas_cmd(datas_prompt.cmds);
    ft_new_free(datas_prompt.env_in_struct);
    if (datas_prompt.out_struct)
        ft_new_free(datas_prompt.out_struct);
    tcsetattr(0, TCSANOW, &datas_prompt.new);
    exit (val_return);
}
