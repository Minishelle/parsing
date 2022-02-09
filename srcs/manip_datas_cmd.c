#include "minishell.h"

t_datas_cmd	*gen_datas_cmd(char *x, t_datas_prompt *datas_prompt, t_var_env *out_struct)
{
	t_datas_cmd	*cmd;

	cmd = malloc(sizeof(t_datas_cmd));
	if (!cmd)
		exit (0);
	cmd->all_cmds = ft_split_up(x);
	cmd->full_path = find_in_env(datas_prompt->envp, "PATH=", 5, 5);
	cmd->cmd_first = trans_cmd(cmd->all_cmds, datas_prompt->envp, out_struct, 0);
	cmd->datas_prompt = datas_prompt;
	cmd->nb_cmds = ft_lstsize(cmd->cmd_first);
	return (cmd);
}
