/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 21:55:30 by user42            #+#    #+#             */
/*   Updated: 2023/03/14 14:03:00 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include "../libft/libft.h"
#include "../include/get_next_line.h"
#include "../include/raycast.h"

void		init_pars(t_parse *pars)
{
	pars->c = -2;
	pars->ea = NULL;
	pars->f = -2;
	pars->no = NULL;
	pars->r.i = 0;
	pars->r.ii = 0;
	pars->r.alr = 0;
	pars->s = NULL;
	pars->so = NULL;
	pars->tab = NULL;
	pars->we = NULL;
	pars->sprites = NULL;
	pars->tabhud = NULL;
	pars->row = 0;
}

char		**ft_lstdtab(t_list *lst)
{
	char	**tab;
	int		i;
	int		size;
	t_list	*next;
	t_list	*list;

	list = lst;
	i = -1;
	size = ft_lstsize(list);
	next = NULL;
	if (size <= 0)
		return (NULL);
	if (!(tab = (char **)malloc((sizeof(char *) * (size + 1)))))
		return (NULL);
	while (i++ < size - 1)
	{
		next = list->next;
		tab[i] = list->content;
		free(list);
		list = next;
	}
	tab[size] = NULL;
	return (tab);
}

int			skip_wspace(char *s)
{
	int n;

	n = 0;
	while (s[n] != '\0' && ft_iswhitespace(s[n]))
		n++;
	return (n);
}

void		init_map_pars(t_cub_skip *map_pars)
{
	map_pars->lst = NULL;
	map_pars->line = NULL;
	map_pars->first = NULL;
	map_pars->hud = NULL;
	map_pars->sprites = NULL;
	map_pars->pars = NULL;
	map_pars->n = 0;
	map_pars->hudrep = 0;
}

int			ft_initdraws(t_draws *ds, t_raycasting *ray, int y)
{
	if (ray->pars->sprites && ray->pars->sprites[y])
	{
		ft_startinitdraws(ds);
		ds->spritex = (ray->pars->sprites[y]->x + 0.5) - ray->posx;
		ds->spritey = (ray->pars->sprites[y]->y + 0.5) - ray->posy;
		ds->invdet = 1.0 / (ray->planex * ray->diry - ray->dirx * ray->planey);
		ds->transformx = ds->invdet * (ray->diry *
									ds->spritex -
									ray->dirx * ds->spritey);
		ds->transformy = ds->invdet * (-ray->planey *
									ds->spritex +
									ray->planex * ds->spritey);
		ds->spritescreenx = ((ray->w / 2) *\
		(1 + ds->transformx / ds->transformy));
		return (1);
	}
	return (0);
}
