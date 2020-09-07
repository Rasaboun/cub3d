/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:52:36 by rasaboun          #+#    #+#             */
/*   Updated: 2019/11/07 14:29:04 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!dst || !src)
		return (0);
	i = 0;
	while (i < (dstsize - 1) && src[i] && dstsize > 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize >= 1)
		dst[i] = '\0';
	return ((size_t)ft_strlen(src));
}
