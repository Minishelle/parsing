/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoorick <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 15:58:47 by hgoorick          #+#    #+#             */
/*   Updated: 2021/09/04 15:58:48 by hgoorick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************ */
/*	Description :															*/
/*			 The strnstr() function locates the	first occurrence of the		*/
/*				null-termi-nated string little in the string big, where 	*/
/*				not more than	len characters are searched.  Characters 	*/
/*				that appear after a `\0'	character are not searched.		*/
/*																			*/
/*	Argument :																*/
/*			big			=>	This is the main C string to be scanned.		*/
/*																			*/
/*			little		=>	This is the small string to be searched with-in */
/*								haystack string.							*/
/*																			*/
/*			len			=>	Number of elements to copy						*/
/*																			*/
/*	Return :																*/
/*			If little is an empty string, big is returned; if little occurs */
/*				nowhere in big, NULL is returned; otherwise a pointer to 	*/
/*				the first character of the first occurrence of little is 	*/
/*				returned.													*/
/* ************************************************************************ */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*h;
	size_t	littleLong;
	size_t	j;
	size_t	i;

	h = (char *)big;
	littleLong = ft_strlen(little);
	if (!littleLong)
		return (h);
	if ((ft_strlen(big) < littleLong) || len < littleLong)
		return (NULL);
	i = 0;
	while (h[i] && i <= len - littleLong)
	{
		j = 0;
		while (little[j] && (little[j] == h[i + j]))
			j++;
		if (j == littleLong)
			return (&h[i]);
		i++;
	}
	return (NULL);
}
