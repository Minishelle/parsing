#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../wraloc/wraloc.h"

# define INPUT "######################################################\n\
#     __  ____       _      __         ____          #\n\
#    /  |/  (_)___  (_)____/ /_  ___  / / /          #\n\
#   / /|_/ / / __ \\/ / ___/ __ \\/ _ \\/ / /           #\n\
#  / /  / / / / / / (__  ) / / /  __/ / /            #\n\
# /_/  /_/_/_/ /_/_/____/_/ /_/\\___/_/_/             #\n\
#                                                    #\n\
# Dev by Lisa Buccheri, Matteo Bucci & Hugo Goorickx #\n\
# (Version 0.1)                                      #\n\
######################################################\n"

typedef struct s_datas_prompt	t_datas_prompt;
typedef struct s_datas_cmd	t_datas_cmd;
typedef struct s_var_env t_var_env;

struct s_datas_prompt
{
	t_datas_cmd	*cmds;
	char		**envp;
	int			nb_cmds;
};

struct s_var_env
{
		char *var_txt;
		char *name_var;
		t_var_env *next;
};

struct s_datas_cmd
{
	char			**all_cmds;
	char			*full_path;
	int				nb_cmds;
	t_one_cmd		*cmd_first;
	t_datas_prompt	*datas_prompt;
};

void	ft_free_one_cmd(t_one_cmd *first_cmd);
void ft_free_datas_cmd(t_datas_cmd *datas_cmd);

int ft_strlen_up(char *str, char *search);
int infile(char **all_cmd);
int outfile(char **all_cmd);

char	*find_in_env(char **envp, char *word, int len_word, int len_return);
char *start_prompt(char **env);

char **ft_first_cmd(char **all_cmds);
char **pipen_t(char **cmds);
char **modif_mat(char **cmds, char **envp);
char **simple_mat(char **start_mat);

t_datas_cmd *gen_datas_cmd(char *x, t_datas_prompt *datas_prompt);
t_datas_cmd *ft_parsing(char *cmd_one_line, t_datas_prompt *datas_prompt);

t_one_cmd	*trans_cmd(char **cmds, char **envp);

#endif

/*
#####################################################\n\
#     __  ____       _      __         ____         #\n\
#    /  |/  (_)___  (_)____/ /_  ___  / / /         #\n\
#   / /|_/ / / __ \/ / ___/ __ \/ _ \/ / /          #\n\
#  / /  / / / / / / (__  ) / / /  __/ / /           #\n\
# /_/  /_/_/_/ /_/_/____/_/ /_/\___/_/_/            #\n\
#                                                   #\n\
# Dev by Lisa Buccheri, Matteo Bucci & Hugo Goorickx#\n\
#                                                   #\n\
#####################################################\n
*/
