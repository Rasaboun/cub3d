/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 23:07:53 by user42            #+#    #+#             */
/*   Updated: 2020/12/18 23:54:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test.h"
#include "../libft/libft.h"
#include "../get_next_line.h"
#include "../raycast.h"

void	ft_rrerror(cub_skip *map_pars, t_list *first)
{
	t_list *next;

	while (first)
	{
		next = first->next;
		ft_lstdelone(first, &free);
		first = next;
	}
	while (map_pars->first)
	{
		next = map_pars->first->next;
		ft_lstdelone(map_pars->first, &free);
		map_pars->first = next;
	}
}

void	ft_rerror(cub_skip *map_pars, t_list *first, char *line, char *str)
{
	t_list *next;

	if (line != NULL)
		free(line);
	ft_rrerror(map_pars, first);
	while (map_pars->hud)
	{
		next = map_pars->hud->next;
		ft_lstdelone(map_pars->hud, &free);
		map_pars->hud = next;
	}
	while (map_pars->lst)
	{
		next = map_pars->lst->next;
		ft_lstdelone(map_pars->lst, &free);
		map_pars->lst = next;
	}
	freeall(map_pars->pars);
	ft_putstr_fd(str, 1);
	exit(0);
}

void	duplicerror(char *s, parse *pars)
{
	if (s != NULL)
		ft_error("duplicate param", pars);
}
