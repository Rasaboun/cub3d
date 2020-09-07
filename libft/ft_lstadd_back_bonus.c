/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 12:07:23 by rasaboun          #+#    #+#             */
/*   Updated: 2019/11/10 12:07:29 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*lst2;

	if (*alst == NULL)
		*alst = new;
	else
	{
		lst2 = ft_lstlast(*alst);
		lst2->next = new;
		new->next = NULL;
	}
}
