/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:33:56 by rasaboun          #+#    #+#             */
/*   Updated: 2019/11/12 18:35:56 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				i;
	unsigned char	*str;
	unsigned char	*str2;

	if (n == 0)
		return (0);
	i = 0;
	str = (unsigned char*)s1;
	str2 = (unsigned char*)s2;
	while ((size_t)i < n - 1 && str[i] == str2[i])
		i++;
	return ((int)(str[i] - str2[i]));
}
