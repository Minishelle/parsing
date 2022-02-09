#include "minishell.h"

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
	ft_putstr_fd("\n", 1);
}

int ft_allisspace(char *str)
{
	int x;

	x = ft_strlen(str);
	while (--x > -1 && (str[x] == '\t' || str[x] == ' '))
		;
	return (x);
}

int ft_strchr_up(const char *str, int to_find)
{
	int x;

	x = 0;
	while (*str != (char)to_find && *str)
	{
		x++;
		str++;
	}
	if (*str == (char)to_find)
		return (x);
	return (0);
}

t_var_env *ft_new_var_env(char *str, t_var_env *old_struct)
{
	int size_word;
	int size_word2;
	t_var_env *out_struct;

	out_struct = malloc(sizeof(t_var_env));
	if (!out_struct)
		exit (0); //free all
	size_word = ft_strchr_up(str, '=');
	out_struct->name_var = malloc(sizeof(char) * size_word);
	ft_strlcpy(out_struct->name_var, str, size_word);
	size_word2 = ft_strlen(str) - size_word;
	out_struct->var_txt = malloc(sizeof(char) * size_word2);
	ft_strlcpy(out_struct->var_txt, &str[size_word + 1], size_word2);
	out_struct->next = old_struct;
	return (out_struct);
}

int	ft_lstsize_up(t_var_env *lst)
{
	if (!lst)
		return (0);
	if (lst->next == 0)
		return (1);
	return (1 + ft_lstsize_up(lst->next));
}

t_var_env *conv_env(char **envp)
{
	int x;
	t_var_env *out_struct;

	x = -1;
	out_struct = NULL;
	while (++x < ft_matrixlen(envp))
		out_struct = ft_new_var_env(envp[x], out_struct);
	return (out_struct);
}

void ft_new_free(t_var_env *input)
{
	t_var_env *tmp;

	while (input->next)
	{
		tmp = input;
		if (tmp->var_txt)
			free(tmp->var_txt);
		if (tmp->name_var)
			free(tmp->name_var);
		input = tmp->next;
		if (tmp)
			free(tmp);
	}
	if (input->var_txt)
		free(input->var_txt);
	if (input->name_var)
		free(input->name_var);
	if (input)
		free(input);
}

int	main(int argc, char **argv, char **envp)
{
	char			*prompt;
    char            *test;
	t_datas_prompt	datas_prompt;
	int 	fd[2];
	fd[0] = -2;
	fd[1] = -2;

	(void)argc;
	(void)argv;
	datas_prompt.envp = envp;
	datas_prompt.env_in_struct = conv_env(envp);
	datas_prompt.nb_cmds = 0;
	datas_prompt.out_struct = NULL;
	datas_prompt.cmds = NULL;
	ft_putstr_fd("\033[2J", 1);
	ft_putstr_fd(INPUT, 1);
	while (datas_prompt.nb_cmds < 5)
	{
		prompt = start_prompt(envp);
        test = readline(prompt);
		if (test[0] && ft_allisspace(test) != -1)
		{
			if (ft_strchr(test, '=') && (ft_strchr(test, '"') == 0 || ft_strchr(test, '"') > ft_strchr(test, '=')))
				datas_prompt.out_struct = ft_new_var_env(test, datas_prompt.out_struct);
			else
			{
				datas_prompt.cmds = gen_datas_cmd(test, &datas_prompt, datas_prompt.out_struct);
				pipex_rec(datas_prompt.cmds, envp, fd, datas_prompt.cmds->cmd_first);
				datas_prompt.nb_cmds++;
				//print_test(datas_prompt);
				ft_free_datas_cmd(datas_prompt.cmds);
			}
			add_history(test);
		}
		free(test);
		free(prompt);
	}
	ft_new_free(datas_prompt.env_in_struct);
	ft_new_free(datas_prompt.out_struct);
}
