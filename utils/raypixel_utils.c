/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raypixel_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 01:07:05 by user42            #+#    #+#             */
/*   Updated: 2020/12/26 14:32:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test.h"
#include "../libft/libft.h"
#include "../get_next_line.h"
#include "../raycast.h"

void		put_pixel(t_raycasting *ray, t_mini mn)
{
	int yy;
	int xx;
	int xtmp;

	xx = 0;
	yy = 0;
	xtmp = mn.ii;
	while (yy < mn.ratio_y)
	{
		xx = 0;
		mn.ii = xtmp;
		while (xx < mn.ratio_x)
		{
			ray->imagescreenb[mn.yy * ray->w + mn.ii] = mn.color;
			mn.ii++;
			xx++;
		}
		mn.yy++;
		yy++;
	}
}

void		utils_mmap(t_raycasting *ray, t_mini *ds)
{
	if (ds->y == (int)ray->posx && ds->i == (int)ray->posy)
		ds->color = 0xfc030b;
	else if (ray->pars->tab && ray->pars->tab[ds->y][ds->i] != '1')
		ds->color = 0x292d2e;
	else
		ds->color = 0x33dcf2;
	while (ray->pars->sprites != NULL &&
		ray->pars->sprites[ds->sp] != NULL)
	{
		if (ds->y == ray->pars->sprites[ds->sp]->x \
		&& ds->i == ray->pars->sprites[ds->sp]->y)
			ds->color = 0xffffff;
		ds->sp++;
	}
	put_pixel(ray, *ds);
	ds->ii += ds->ratio_x;
	ds->i++;
	ds->sp = 0;
}

void		mini_map(t_raycasting *ray)
{
	t_mini ds;

	ds.ratio_x = ((ray->w / 8) - (ray->w / (16 * 2))) / ray->pars->width;
	ds.ratio_y = ((ray->h / 8) - (ray->h / (16 * 2))) / ray->pars->height;
	ds.ii = 0;
	ds.i = 0;
	ds.y = 0;
	ds.yy = 0;
	ds.sp = 0;
	while (ds.y < ray->pars->height)
	{
		ds.i = 0;
		ds.ii = 0;
		while (ds.i < ray->pars->width)
		{
			utils_mmap(ray, &ds);
		}
		ds.yy += ds.ratio_y;
		ds.y++;
	}
}

void		mini_life(t_raycasting *ray)
{
	t_mini mn;

	if (ray->pars->tabhud == NULL)
		return ;
	mn.ratio_x = (((ray->w / 5) - (ray->w / (16 * 2))) / ray->pars->hwidth);
	mn.ratio_y = (((ray->w / 20) - (ray->w / (16 * 2))) / ray->pars->hheight);
	mn.ii = (int)(ray->w / 1.2);
	mn.i = 0;
	mn.y = -1;
	mn.yy = ray->w / ray->h;
	while (mn.y++ < (ray->pars->hheight - 1))
	{
		mn.i = 0;
		mn.ii = (int)(ray->w / 1.2);
		while (mn.i < ray->pars->hwidth)
		{
			mn.color = 0xc21316;
			if (ray->pars->tabhud[mn.y][mn.i] == '4'\
			|| ray->pars->tabhud[mn.y][mn.i] == '6')
				put_pixel(ray, mn);
			mn.ii += mn.ratio_x;
			mn.i++;
		}
		mn.yy += mn.ratio_y;
	}
}
