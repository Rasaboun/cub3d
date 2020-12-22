/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 12:24:56 by rasaboun          #+#    #+#             */
/*   Updated: 2020/12/22 01:57:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_while(char *s3, const char *s1, int i)
{
	int		p;
	int		y;

	p = 0;
	y = 0;
	while (p < i)
	{
		s3[p] = s1[y];
		p++;
		y++;
	}
	return (p);
}

char		*ft_strfjoin(char *s1, char *s2)
{
	int		p;
	char	*s3;
	int		y;
	int		i;

	if (!s1 || s2 == NULL)
		return (NULL);
	y = 0;
	p = 0;
	i = (int)ft_strlen(s1);
	if (!(s3 = (char *)malloc(sizeof(char) * (i + ft_strlen(s2) + 1))))
		return (0);
	p = ft_while(s3, s1, i);
	y = 0;
	while (p <= (int)(i + ft_strlen(s2) - 1))
	{
		s3[p] = s2[y];
		p++;
		y++;
	}
	s3[p] = '\0';
	free(s2);
	free(s1);
	return (s3);
}
