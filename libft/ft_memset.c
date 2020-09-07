/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:34:56 by rasaboun          #+#    #+#             */
/*   Updated: 2019/11/12 19:06:24 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	int				i;
	unsigned char	*str;

	str = (unsigned char*)b;
	i = 0;
	while ((size_t)i < n)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
