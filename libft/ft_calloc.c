/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:30:30 by rasaboun          #+#    #+#             */
/*   Updated: 2019/11/12 19:03:07 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*malzero(size_t size)
{
	void	*temp;

	if (!(temp = malloc(size)))
		return (NULL);
	ft_bzero(temp, size);
	return (temp);
}

void		*ft_calloc(size_t count, size_t size)
{
	void	*tab;

	if (!(tab = (void*)malzero(size * count)))
		return (NULL);
	return (tab);
}
