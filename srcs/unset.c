/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 11:43:51 by mbucci            #+#    #+#             */
/*   Updated: 2022/02/24 15:09:23 by mbucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (tmp->var_txt)
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
	datas_prompt.last_command_status = status;
}