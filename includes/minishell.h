#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
//# include "../wraloc/wraloc.h"

//p
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>

# define INPUT "######################################################\n\
#     __  ____       _      __         ____          #\n\
#    /  |/  (_)___  (_)____/ /_  ___  / / /          #\n\
#   / /|_/ / / __ \\/ / ___/ __ \\/ _ \\/ / /           #\n\
#  / /  / / / / / / (__  ) / / /  __/ / /            #\n\
# /_/  /_/_/_/ /_/_/____/_/ /_/\\___/_/_/             #\n\
#                                                    #\n\
# Dev by Lisa Buccheri, Matteo Bucci & Hugo Goorickx #\n\
# (Version 0.5)                                      #\n\
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

//pipex_rec

typedef struct s_fd
{
	int	f_in;
	int	f_out;
}	t_fd;

//int		count(char const *s, char c);
void	ft_free(char **paths, char **cmd);
void	close_pipe(int fd[2]);
void	parent(t_fd fds, char *argv[], char *env[], int fd[2]);
void	child(t_fd fds, char *argv[], char *env[], int fd[2]);
char	**get_path(char *env[]);
//char	**null_return(int i, char **t);
//char	**alloc_memory(int len, char **t, char const *s, char c);
void	perror_cnf(char *str, char *cmd, int fd);
void	ft_end_process(char *cmd_path, char **cmd, char **path, char **env);
void	process(char *env[], char **cmd);
int		count_cmd(char *argv[]);
void 	cmd_process(t_fd fds, char **argv, char *env[], int j);
void 	pipex_rec(t_datas_cmd *cmds, char *env[], int prev_fd[2], t_one_cmd *cmd);

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
