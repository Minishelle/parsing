/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:49:11 by mbucci            #+#    #+#             */
/*   Updated: 2022/02/23 16:46:23 by mbucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	export name
 *	if name is already a variable it will be added to env
 *	if name has no value name
 * */

/*void	export(int ac, char **av)
{
	int	i;

	// check for forbidden characters
	// if no parameter is given
	if (ac == 1)
	{
		// display all exported variables in alphabetic order
	}
	else
	{
		i = 0;
		while (++i < ac)
		{
			//	if (av[i] in sys_var or var does not have a value)
				//	add to env list + delete sys_var list;
		}
	}
}*/

/*void	print_list(void)
{
	t_var_env	*ptr;

	ptr = datas_prompt.env_in_struct;
	while (ptr)
	{
		printf("%s=%s\n", ptr->name_var, ptr->var_txt);
		ptr = ptr->next;
	}
}*/

/*void	print_matrix(char **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
		printf("%s\n", matrix[i]);
}*/

void	var_error(char *funct, char *var)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(funct, STDERR_FILENO);
	ft_putstr_fd(": `", STDERR_FILENO);
	ft_putstr_fd(var, STDERR_FILENO);
	ft_putstr_fd("': ", STDERR_FILENO);
	ft_putendl_fd("not a valid identifier", STDERR_FILENO);
}

int	check_char_in_name(char *funct, char *s, int *ptr)
{
	int	i;

	i = -1;
	while (s[++i] && (ft_isalpha(s[i]) || (i != 0 && ft_isdigit(s[i])) || s[i] == '_'))
		;
	if (!s[i])
		return (0);
	else
	{
		var_error(funct, s);
		*ptr = 1;
	}
	return (1);
}

void	ft_remove_link(t_var_env *target, t_var_env **list)
{
	t_var_env	*tmp;
	t_var_env	*ptr;

	if (!list || !*list || !target)
		return ;
	ptr = *list;
	if (target == ptr)
	{
		tmp = ptr;
		*list = (*list)->next;
	}
	else
	{
		while (ptr && ptr->next && ptr->next != target)
			ptr = ptr->next;
		tmp = ptr->next;
		if (ptr->next->next)
			ptr->next = ptr->next->next;
		else
			ptr->next = NULL;
	}
	free(tmp->var_txt);
	free(tmp->name_var);
	free(tmp);
}

void	unset(int ac, char **av)
{
	int			i;
	int			status;
	t_var_env	*found;

	if (ac == 1)
	{
		datas_prompt.last_command_status = 0;
		return ;
	}
	i = -1;
	status = 0;
 	while (++i < ac)
	{
		if (check_char_in_name("unset", av[i], &status))
			continue ;
		found = ft_find_in_list(av[i], datas_prompt.env_in_struct);
		if (found)
			ft_remove_link(found, &datas_prompt.env_in_struct);
		else
		{
			found = ft_find_in_list(av[i], datas_prompt.out_struct);
			if (found)
				ft_remove_link(found, &datas_prompt.out_struct);
		}
	}
	ft_clean_mat(datas_prompt.envp);
	datas_prompt.envp = conv_env_to_mat();
	if (!status)
		datas_prompt.last_command_status = 0;
}

void	ft_exit(void)
{
	char **tmp;

	tmp = malloc(sizeof(char *) * 3);
	tmp[0] = "rm";
	tmp[1] = "-f";
	tmp[2] = "tmp";
	execve("/bin/rm", tmp, datas_prompt.envp);
	ft_free_datas_cmd(datas_prompt.cmds);
	ft_new_free(datas_prompt.env_in_struct);
	if (datas_prompt.out_struct)
		ft_new_free(datas_prompt.out_struct);
	exit(0);
}
