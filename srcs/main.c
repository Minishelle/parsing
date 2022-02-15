/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoorick <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 18:14:40 by hgoorick          #+#    #+#             */
/*   Updated: 2022/02/10 18:14:42 by hgoorick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/****************************************
*
*	Nom : print_test
*	Params : Strcut de datas_prompt
*	Retour : void
*	Descritpion:
*		Affiche le contenu de toutes les commandes une par une
*
****************************************/
/*
void	print_test(t_datas_prompt datas_prompt)
{
	int			y;
	t_one_cmd	*x;

	x = datas_prompt.cmds->cmd_first;
	while (x->next)
	{
		ft_putstr_fd("\n------------------------\nCmd : ", 1);
		ft_putstr_fd(x->cmd, 1);
		ft_putstr_fd("\nParams : ", 1);
		y = 0;
		while (++y < ft_matrixlen(x->all_cmd))
		{
			ft_putstr_fd(x->all_cmd[y], 1);
			ft_putstr_fd(" ", 1);
		}
		ft_putstr_fd("\nInfile Outfile : ", 1);
		ft_putnbr_fd(x->infile, 1);
		ft_putstr_fd(" ", 1);
		ft_putnbr_fd(x->outfile, 1);
		ft_putstr_fd("\nType next : ", 1);
		ft_putnbr_fd(x->type_next, 1);
		ft_putstr_fd("\nType hd : ", 1);
		ft_putnbr_fd(x->type_hd, 1);
		ft_putstr_fd("\nMagic word : ", 1);
		ft_putstr_fd(x->magic_word, 1);
		x = x->next;
	}
	ft_putstr_fd("\n------------------------\nCmd : ", 1);
	ft_putstr_fd(x->cmd, 1);
	ft_putstr_fd("\nParams : ", 1);
	y = 0;
	while (++y < ft_matrixlen(x->all_cmd))
	{
		ft_putstr_fd(x->all_cmd[y], 1);
		ft_putstr_fd(" ", 1);
	}
	ft_putstr_fd("\nInfile Outfile : ", 1);
	ft_putnbr_fd(x->infile, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(x->outfile, 1);
	ft_putstr_fd("\nType next : ", 1);
	ft_putnbr_fd(x->type_next, 1);
	ft_putstr_fd("\nType hd : ", 1);
	ft_putnbr_fd(x->type_hd, 1);
	ft_putstr_fd("\nMagic word : ", 1);
	ft_putstr_fd(x->magic_word, 1);
	ft_putstr_fd("\n", 1);
}*/


/****************************************
*
*	Nom : init_data_prompt
*	Params : Pointeur de la struct datas_prompt
*	Retour : void
*	Descritpion:
*		init les donnees de bases pour la struct datas_prompt
*
****************************************/

void	init_data_prompt(t_datas_prompt *datas_prompt, char **envp)
{
	datas_prompt->envp = envp;
	datas_prompt->env_in_struct = conv_env(envp);
	if (!datas_prompt->env_in_struct)
		exit(1);
	datas_prompt->nb_cmds = 0;
	datas_prompt->out_struct = NULL;
	datas_prompt->cmds = NULL;
	ft_putstr_fd("\033[2J", 1);
	ft_putstr_fd(INPUT, 1);
}

int	main(int argc, char **argv, char **envp)
{
	char			*prompt;
	char			*test;
	t_datas_prompt	datas_prompt;
	int				fd[2];

	fd[0] = 6;
	fd[1] = 6;
	(void)argc;
	(void)argv;
	init_data_prompt(&datas_prompt, envp);
	while (datas_prompt.nb_cmds < 5)
	{
		prompt = start_prompt(envp);
		test = readline(prompt);
		if (test[0] && ft_allisspace(test) != -1)
		{
			if (ft_strchr(test, '=') && (ft_strchr(test, '"') == 0 || ft_strchr(test, '"') > ft_strchr(test, '=')))
			{
				datas_prompt.out_struct = ft_new_var_env(test, datas_prompt.out_struct);
				if (!datas_prompt.out_struct)
					exit (0);
			}
			else
			{
				datas_prompt.cmds = gen_datas_cmd(test, &datas_prompt);
				if (!datas_prompt.cmds)
				{
					ft_new_free(datas_prompt.env_in_struct);
					ft_new_free(datas_prompt.out_struct);
					exit (0);
				}
			//	print_test(datas_prompt);
				if (datas_prompt.cmds->cmd_first->type_hd == 1)
					ft_here_doc(datas_prompt.cmds, datas_prompt.cmds->cmd_first->magic_word);
				pipex_rec(datas_prompt.cmds, envp, fd, datas_prompt.cmds->cmd_first);
				datas_prompt.nb_cmds++;
				ft_free_datas_cmd(datas_prompt.cmds);
			}
			add_history(test);
		}
		free(test);
		free(prompt);
	}
	ft_new_free(datas_prompt.env_in_struct);
	if (datas_prompt.out_struct)
		ft_new_free(datas_prompt.out_struct);
}
