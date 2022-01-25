/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoorick <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 15:57:03 by hgoorick          #+#    #+#             */
/*   Updated: 2021/09/04 15:57:05 by hgoorick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************ */
/*	Description :															*/
/*			Allocate and return an array of strings obtained by separating 	*/
/*				's' from using the 'c' character, used as a delimiter.		*/
/*				The array must be terminated with NULL.						*/
/*																			*/
/*	Argument :																*/
/*			s	=>		The string of characters to cut.					*/
/*			c	=>		The delimiting character.							*/
/*																			*/
/*	Return :																*/
/*			The array of new strings, resulting from the splitting. 		*/
/*				NULL if the allocation fails.								*/
/* ************************************************************************ */

#include "libft.h"

static char	**ft_clean(char **s, int i)
{
	while (i--)
		free(s[i]);
	return (0);
}

static int need_line(int status, int lg_world)
{
	if ((status && lg_world) || (!status && !lg_world))
		return (1);
	return (0);
}

static int len_word(char const *s, int i)
{
	int	lgWord;
	int status;

	lgWord = 0;
	status = 0;
	while (s[i + lgWord] && (!ft_isspace(s[i + lgWord]) || status))
	{
		if ((s[i + lgWord] == '"') && !status)
			status = 1;
		else if ((s[i + lgWord] == 39) && !status)
			status = 2;
		else if (((s[i + lgWord] == 39) && status == 2) ||
			((s[i + lgWord] == '"') && status == 1) ||
			(!status && (s[i + lgWord] == '|' || s[i + lgWord] == '>' ||
			s[i + lgWord] == '<')))
		{
			if (!status && (s[i + lgWord] == s[i + lgWord + 1] ||
			 	s[i + lgWord] == s[i + lgWord + 1]))
				lgWord += need_line(status, lgWord) * 2;
			else
				lgWord += need_line(status, lgWord);
			break;
		}
		lgWord++;
	}
	return (lgWord);
}

static int	nbWords(char const *s)
{
	int	i;
	int	nbWords;
	int	lgWord;

	i = 0;
	nbWords = 0;
	while (s[i])
	{
		while (s[i] && (ft_isspace(s[i])))
			i++;
		lgWord = len_word(s, i);
		if (lgWord)
			nbWords++;
		i += lgWord;
	}
	return (nbWords);
}

static char	**ft_split2(char const *s, char **retour, unsigned int nb)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	lgWord;

	i = 0;
	j = 0;
	while (i < nb)
	{
		while (s[j] && (ft_isspace(s[j])))
			j++;
		lgWord = len_word(s, j);
		retour[i] = malloc(sizeof(char) * (lgWord + 1));
		if (!retour[i])
			return (ft_clean(retour, i));
		ft_strlcpy(retour[i], &s[j], lgWord);
		j += lgWord;
		i++;
	}
	return (retour);
}

char	**ft_split_up(char const *s)
{
	unsigned int	nbWord;
	char			**retour;

	if (!s)
		return (0);
	nbWord = nbWords(s);
	retour = malloc(sizeof(char *) * (nbWord + 1));
	if (!retour)
		return (0);
	retour = ft_split2(s, retour, nbWord);
	if (!retour)
	{
		free(retour);
		return (0);
	}
	retour[nbWord] = 0;
	return (retour);
}
