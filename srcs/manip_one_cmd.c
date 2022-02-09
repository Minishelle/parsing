#include "minishell.h"

t_one_cmd	*trans_cmd(char **cmds, char **envp, t_var_env *out_struct, int status)
{
	int			x;
	t_one_cmd	*cmd;

	cmds = pipen_t(cmds);
	if (!cmds)
		return (NULL);
	cmd = malloc(sizeof(t_one_cmd));
	if (!cmd)
		exit(0); //free
	cmd->all_cmd = ft_matrixlcpy(cmds, find_next_char(cmds, '|'));
	cmd->all_cmd = modif_mat(cmd->all_cmd, envp, out_struct);
	cmd->infile = infile(cmd->all_cmd);
	cmd->outfile = outfile(cmd->all_cmd);
	if (cmd->infile != 0 || cmd->outfile != 1)
		cmd->all_cmd = simple_mat(cmd->all_cmd);
	cmd->cmd = cmd->all_cmd[0];
	x = find_next_char(cmds, '|');
	cmd->type_next = 0;
	cmd->next = NULL;
	if (x != ft_matrixlen(cmds))
	{
		if (status)
			cmd->type_next = 1;
		else
			cmd->type_next = 2;
		cmd->next = trans_cmd(&(cmds[x + 1]), envp, out_struct, 1);
	}
	return(cmd);
}
