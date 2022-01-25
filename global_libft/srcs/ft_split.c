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

static int	nbWords(char const *s, char c)
{
	int	i;
	int	nbWords;
	int	lgWord;

	i = 0;
	nbWords = 0;
	while (s[i])
	{
		while (s[i] && (c == s[i]))
			i++;
		lgWord = 0;
		while (s[i + lgWord] && (c != s[i + lgWord]))
			lgWord++;
		if (lgWord)
			nbWords++;
		i += lgWord;
	}
	return (nbWords);
}

static char	**ft_split2(char const *s, char c, char **retour, unsigned int nb)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	lgWord;

	i = 0;
	j = 0;
	while (i < nb)
	{
		while (s[j] && (c == s[j]))
			j++;
		lgWord = 0;
		while (s[j + lgWord] && (c != s[j + lgWord]))
			lgWord++;
		retour[i] = malloc(sizeof(char) * (lgWord + 1));
		if (!retour[i])
			return (ft_clean(retour, i));
		ft_strlcpy(retour[i], &s[j], lgWord + 1);
		j += lgWord;
		i++;
	}
	return (retour);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	nbWord;
	char			**retour;

	if (!s)
		return (0);
	nbWord = nbWords(s, c);
	retour = malloc(sizeof(char *) * (nbWord + 1));
	if (!retour)
		return (0);
	retour = ft_split2(s, c, retour, nbWord);
	if (!retour)
	{
		free(retour);
		return (0);
	}
	retour[nbWord] = 0;
	return (retour);
}
