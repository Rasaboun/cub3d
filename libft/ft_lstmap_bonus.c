/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 12:08:34 by rasaboun          #+#    #+#             */
/*   Updated: 2019/11/11 15:12:41 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*clst;
	t_list	*start;

	if (!(lst) || !(f))
		return (NULL);
	start = 0;
	while (lst)
	{
		if (!(clst = ft_lstnew(f(lst->content))))
			ft_lstclear(&start, del);
		ft_lstadd_back(&start, clst);
		lst = lst->next;
	}
	return (start);
}
