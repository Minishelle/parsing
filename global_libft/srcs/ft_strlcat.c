/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoorick <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 15:57:55 by hgoorick          #+#    #+#             */
/*   Updated: 2021/09/04 15:57:56 by hgoorick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************ */
/*	Description :															*/
/*			strlcat() appends string src to the end of dst. It will append	*/
/*				at most dstsize - strlen(dst) - 1 characters. It will then	*/
/*				NUL-terminate, unless dstsize is 0 or the original dst		*/
/*				string was longer than dstsize.								*/
/*																			*/
/*	Argument :																*/
/*			dst		=>	String where 'src' will be added.					*/
/*			src		=>	String which will be added to 'dst'.				*/
/*			siz		=>	Number of byts to add to 'dst'.						*/
/*																			*/
/*	Return :																*/
/*			The initial length of dst and the length of src. If the return 	*/
/*				value is >= dstsize, the output string has been truncated. 	*/
/*				It is the caller's responsibility to handle this.			*/
/* ************************************************************************ */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	srcLong;
	size_t	dstLong;
	size_t	i;

	srcLong = -1;
	dstLong = 0;
	i = 0;
	while (dst[dstLong] && dstLong < siz)
		dstLong++;
	while (src[++srcLong])
		if (dstLong + srcLong < siz - 1 && siz)
			dst[dstLong + (i++)] = src[srcLong];
	if (siz && dstLong < siz)
		dst[dstLong + i] = '\0';
	return (dstLong + srcLong);
}
