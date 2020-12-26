/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 21:20:11 by user42            #+#    #+#             */
/*   Updated: 2020/12/26 14:42:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test.h"
#include "../libft/libft.h"
#include "../get_next_line.h"
#include "../raycast.h"

t_list	*recupmap(int fd, char *line, t_cub_skip *map_pars)
{
	t_list	*first;
	t_list	*map;

	first = NULL;
	map = NULL;
	first = ft_lstnew(line);
	while (get_next_line(fd, &line) && line != NULL)
	{
		if (line[skip_wspace(line)] != '1')
			ft_rerror(map_pars, first, line, "ERROR MAP");
		map = ft_lstnew(line);
		ft_lstadd_back(&first, map);
	}
	map = ft_lstnew(line);
	ft_lstadd_back(&first, map);
	return (first);
}

t_list	*recuphud(int fd, char *line, t_cub_skip *map_pars)
{
	t_list	*first;
	t_list	*map;

	first = NULL;
	map = NULL;
	map_pars->hudrep += 1;
	if (map_pars->hudrep >= 2)
		ft_rerror(map_pars, NULL, line, "ERROR HUD\n");
	first = ft_lstnew(line);
	while (get_next_line(fd, &line) && line[skip_wspace(line)] == '5')
	{
		map = ft_lstnew(line);
		ft_lstadd_back(&first, map);
	}
	if (line[skip_wspace(line)] != '5')
	{
		free(line);
		return (first);
	}
	map = ft_lstnew(line);
	ft_lstadd_back(&first, map);
	return (first);
}
