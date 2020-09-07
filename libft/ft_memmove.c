/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:34:50 by rasaboun          #+#    #+#             */
/*   Updated: 2019/11/12 18:55:37 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	int					i;
	unsigned char		*str;
	const unsigned char	*str2;

	str = (unsigned char*)dst;
	str2 = (unsigned char*)src;
	i = 0;
	if (dst <= src)
		ft_memcpy(dst, src, n);
	else
	{
		str = dst + n - 1;
		str2 = src + n - 1;
		while (n--)
		{
			str[i] = str2[i];
			i--;
		}
	}
	return (dst);
}
