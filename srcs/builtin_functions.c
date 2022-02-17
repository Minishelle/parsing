/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:49:11 by mbucci            #+#    #+#             */
/*   Updated: 2022/02/15 12:55:47 by mbucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"

int	ft_open(t_one_cmd *cmd)
{
	int	fd;

	if (!cmd->type_next)
		return (1);
	fd = open("tmp_build", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return(0);
	cmd->infile = fd;
	return (fd);
}

void	cd(int ac, char **av)
{
	int	ret;

	if (ac == 1)
	{
		if (!ft_getenv("HOME", datas_prompt.env_in_struct))
			perror("HOME not set");
		else
		{
			ret = chdir(ft_getenv("HOME", datas_prompt.env_in_struct));
			if (ret)
				perror(NULL);
		}
	}
	else
	{
		ret = chdir(av[1]);
		if (ret == -1)
			perror(NULL);
	}
}


/*	EXPORT NAME
 *	if NAME is already a variable it will be added to env
 *	if NAME has no value NAME
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
				//	add to env list + delete sys_var List;
		}
	}
}

void	unset(int ac, char **av)
{
	int	i;

	if (ac == 1)
		return ;
	i = 0;
 	while (++i < ac)
	{
		//	if (av[i] in env)
		//		delete element;
		//	else if (av[i] in sys_var)
		//		delete element;
		//	else
		//		;
	}
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
