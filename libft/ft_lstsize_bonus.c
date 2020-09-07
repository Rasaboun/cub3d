/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 12:08:54 by rasaboun          #+#    #+#             */
/*   Updated: 2019/11/10 12:08:58 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*lst2;
	int		i;

	lst2 = lst;
	i = 0;
	while (lst2 != NULL)
	{
		lst2 = lst2->next;
		i++;
	}
	return (i);
}
