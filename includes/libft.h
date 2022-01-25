/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoorick <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 15:59:57 by hgoorick          #+#    #+#             */
/*   Updated: 2021/09/06 13:59:41 by hgoorick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
//# include "../wraloc/wraloc.h"

typedef struct s_one_cmd	t_one_cmd;

struct s_one_cmd
{
	char			**all_cmd;
	char			*cmd;
	char			*params;
	int				infile;
	int				outfile;
	int				type_next;
	t_one_cmd		*next;
};

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

char	**ft_split_up(char const *s);

char	**ft_matrixlcpy(char **matrix_in, int nb_line);

int	find_next_char(char **all_cmds, char c);
int ft_isspace(char c);

int		ft_atoi(const char *str);

int		ft_matrixlen(char **m);

int		ft_lstsize(t_one_cmd *lst);

int		ft_isalnum(int c);

int		ft_isalpha(int c);

int		ft_isascii(int c);

int		ft_isdigit(int c);

int		ft_isprint(int c);

int		ft_tolower(int c);

int		ft_toupper(int c);

int		ft_memcmp(const void *string1, const void *string2, size_t size);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*get_next_line(int fd);

char	*ft_strchr(const char *str, int to_find);

char	*ft_strrchr(const char *s, int c);

char	*ft_strdup(const char *src);

char	*ft_strjoin(char const *s1, char const *s2);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

char	*ft_itoa(int n);

char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_strtrim(char const *s1, char const *set);

char	*ft_strnstr(const char *big, const char *little, size_t len);

char	**ft_split(char const *s, char c);

size_t	ft_strlen(const char *str);

size_t	ft_strlcpy(char *dst, const char *src, size_t siz);

size_t	ft_strlcat(char *dst, const char *src, size_t siz);

t_list	*ft_lstnew(void *content);

t_list	*ft_lstlast(t_list *lst);

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

void	ft_putchar_fd(char c, int fd);

void	ft_lstiter(t_list *lst, void (*f)(void *));

void	ft_lstclear(t_list **lst, void (*del)(void *));

void	ft_lstadd_front(t_list **alst, t_list *new);

void	ft_lstdelone(t_list *lst, void (*del)(void *));

void	ft_lstadd_back(t_list **alst, t_list *new);

void	ft_putnbr_fd(int n, int fd);

void	ft_putstr_fd(char *str, int fd);

void	ft_putendl_fd(char *s, int fd);

void	ft_bzero(void *pointer, size_t count);

void	ft_striteri(char *s, void (*f)(unsigned int, char*));

void	*ft_memchr(const void *s, int c, size_t n);

void	*ft_memcpy(void *destination, const void *source, size_t size);

void	*ft_memmove(void *destination, const void *source, size_t size);

void	*ft_memset(void *pointer, int value, size_t count);

void	*ft_calloc(size_t count, size_t size);

#endif
