/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:52:42 by rasaboun          #+#    #+#             */
/*   Updated: 2019/11/07 14:29:14 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int				i;
	unsigned int	n;
	char			*s2;

	if (!s)
		return (NULL);
	n = 0;
	i = (int)ft_strlen(s);
	if (!(s2 = malloc(sizeof(char) * (i + 1))))
		return (0);
	while (s[n] != '\0')
	{
		s2[n] = f(n, s[n]);
		n++;
	}
	s2[n] = '\0';
	return (s2);
}
