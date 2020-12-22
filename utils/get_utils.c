/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 21:17:44 by user42            #+#    #+#             */
/*   Updated: 2020/12/22 01:37:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test.h"
#include "../libft/libft.h"
#include "../get_next_line.h"
#include "../raycast.h"

void	get_sprites(t_cub_skip *map_pars)
{
	int		i;
	t_list	*tmp;

	i = ft_lstsize(map_pars->lst);
	if (map_pars->lst != NULL)
	{
		map_pars->pars->sprites =\
			(t_sprite **)malloc(sizeof(t_sprite *) * (i + 1));
		while (i >= 0)
		{
			map_pars->pars->sprites[i] = NULL;
			i--;
		}
		i = 0;
		while (map_pars->lst != NULL)
		{
			tmp = map_pars->lst->next;
			map_pars->pars->sprites[i] = (t_sprite *)map_pars->lst->content;
			free(map_pars->lst);
			map_pars->lst = tmp;
			i++;
		}
		map_pars->pars->sprites[i] = NULL;
	}
}

void	ft_getplayermap(t_parse *pars, t_checkmap *ck)
{
	ck->play = ft_strchr("NSWE", ck->mapf);
	pars->play.x = ck->i;
	pars->play.y = ck->j;
	pars->play.direction = ck->mapf;
	ck->player++;
	pars->tab[ck->i][ck->j] = '0';
}

void	ft_getspritemap(t_checkmap *ck, t_list **lst)
{
	ck->sprites = malloc(sizeof(t_sprite));
	ck->sprites->x = ck->i;
	ck->sprites->y = ck->j;
	ck->new = ft_lstnew(ck->sprites);
	ft_lstadd_back(lst, ck->new);
}

int		ft_getelemmap(t_parse *pars, t_checkmap *ck, t_list **lst)
{
	ck->mapf = pars->tab[ck->i][ck->j];
	if (!(ft_strchr("012 NSWE", ck->mapf)))
		return (0);
	if (ft_strchr("NSWE", ck->mapf))
		ft_getplayermap(pars, ck);
	if (ft_strchr("2", ck->mapf))
		ft_getspritemap(ck, lst);
	if (ck->mapf == '0' || ck->mapf == '2' || ck->mapf == 'N' ||
		ck->mapf == 'S' || ck->mapf == 'W' || ck->mapf == 'E')
		if (!(close_map(pars, ck->i, ck->j)))
			return (0);
	return (1);
}
