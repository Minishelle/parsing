/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:49:11 by mbucci            #+#    #+#             */
/*   Updated: 2022/02/24 16:26:06 by mbucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	export name
 *	if name is already a variable it will be added to env
 *	if name has no value name
 * */

/*void	sort_env(char **tab)
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
				tba[i] = tab[j];
				tab[j] = t;
			}
		}
	}
}

void	export_print(t_var_env *list)
{
	t_var_env	*save;
	char		*current;

	if (!list)
		return ;
	save = list;
	current = list->name_var;
	while (list1)
	{
		
	}
}

void	export(int ac, char **av)
{
	int	i;
	int	status;

	if (ac == 1)
	{
		export_print(datas_prompt.env_in_struct);
		return ;
	}
	status = 0;
	else
	{
		i = 0;
		while (++i < ac)
		{
			if (check_char_in_name("export", av[i], &status))
				continue ;
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
