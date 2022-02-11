/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_one_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoorick <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 18:35:02 by hgoorick          #+#    #+#             */
/*   Updated: 2022/02/10 18:35:05 by hgoorick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/****************************************
*
*	Nom : trans_cmd
*	Params : - La matrice de toute la ligne de commandes
* 			 - La matrice d'env
*			 - la liste chainee de variables d'environnement defini par le user
*			 - Le status de la fonction (si premier de la liste chainee = 0
*					else = 1)
*	Retour : La premiere structure de la liste chainee de one_cmd
*	Descritpion:
*		Commence par cree la matrice reprenant tous les elements de la commande
*			(jusqu'au pipe), init infile et outfile, met en avant la cmd unique
*			et defini le type du pointeru vers la prochaine commande (0 = pas de
*			commandes apres, 1 = une commande apres, 2 = une commande apres mais
*			celle-ci est la premiere) ensuite il lance relance la fonction avec
*			la commande suivante (si il y en a une)
*
****************************************/

t_one_cmd	*trans_cmd(char **cmds, t_datas_prompt *datas_prompt, int st, t_one_cmd *old_one)
{
	int			x;
	t_one_cmd	*cmd;
	char **envp;
	t_var_env *out_struct;

	envp = datas_prompt->envp;
	out_struct = datas_prompt->out_struct;
	cmds = pipen_t(cmds);
	if (!cmds)
		return (NULL);
	cmd = malloc(sizeof(t_one_cmd));
	if (!cmd)
		exit(0); //free
	cmd->all_cmd = ft_matrixlcpy(cmds, find_next_char(cmds, '|'));
	cmd->all_cmd = modif_mat(cmd->all_cmd, envp, out_struct);
	if (old_one)
	{
		ft_putstr_fd("Nique ta soeur", 1);
		cmd->infile = old_one->infile;
		cmd->outfile = old_one->outfile;
	}
	else
	{
		ft_putstr_fd("Nique ta cousine", 1);
		cmd->infile = infile(cmd->all_cmd);
		cmd->outfile = outfile(cmd->all_cmd);
		if (cmd->infile != 0 || cmd->outfile != 1)
			cmd->all_cmd = simple_mat(cmd->all_cmd);
	}
	x = find_next_char(cmds, '|');
	if (!ft_matrixlen(cmd->all_cmd) && 	x != ft_matrixlen(cmds))
	{
		ft_putstr_fd("Nique ta mere", 1);
		cmd->next = trans_cmd(&(cmds[x + 1]), datas_prompt, 1, cmd);
	}
	else
	{
		cmd->cmd = cmd->all_cmd[0];
		cmd->type_next = 0;
		cmd->next = NULL;
		if (x != ft_matrixlen(cmds))
		{
			cmd->type_next = 2;
			if (st)
				cmd->type_next = 1;
			cmd->next = trans_cmd(&(cmds[x + 1]), datas_prompt, 1, NULL);
		}
	}
	return (cmd);
}
