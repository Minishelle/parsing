#include "minishell.h"

void	ft_free_one_cmd(t_one_cmd *first_cmd)
{
	int	x;

	x = ft_matrixlen(first_cmd->all_cmd);
	while (--x >= 0)
		if (first_cmd->all_cmd[x])
			free(first_cmd->all_cmd[x]);
	if (first_cmd->all_cmd)
		free(first_cmd->all_cmd);
	if (first_cmd->next)
		ft_free_one_cmd(first_cmd->next);
	if (first_cmd)
		free(first_cmd);
}

void	ft_free_datas_cmd(t_datas_cmd *datas_cmd)
{
	int	x;

	if (datas_cmd->full_path)
		free(datas_cmd->full_path);
	if (datas_cmd->all_cmds)
	{
		x = ft_matrixlen(datas_cmd->all_cmds);
		while (--x >= 0)
			free(datas_cmd->all_cmds[x]);
		free(datas_cmd->all_cmds);
	}
	if (datas_cmd->cmd_first)
		ft_free_one_cmd(datas_cmd->cmd_first);
	if (datas_cmd)
		free(datas_cmd);
}
