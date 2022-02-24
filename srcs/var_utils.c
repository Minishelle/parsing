/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 11:45:30 by mbucci            #+#    #+#             */
/*   Updated: 2022/02/24 14:48:42 by mbucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_char_in_name(char *funct, char *s, int *ptr)
{
	int	i;

	i = -1;
	while (s[++i] && (ft_isalpha(s[i]) || (i != 0 && ft_isdigit(s[i]))
			|| s[i] == '_' || (!ft_strcmp("export", funct) && s[i] == '=')))
		;
	if (!s[i])
		return (0);
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(funct, STDERR_FILENO);
		ft_putstr_fd(": `", STDERR_FILENO);
		ft_putstr_fd(s, STDERR_FILENO);
		ft_putstr_fd("': ", STDERR_FILENO);
		ft_putendl_fd("not a valid identifier", STDERR_FILENO);
		*ptr = 1;
	}
	return (1);
}

/*int	check_definition(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		
}*/
