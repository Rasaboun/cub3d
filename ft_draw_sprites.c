/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 19:08:33 by user42            #+#    #+#             */
/*   Updated: 2020/12/16 22:25:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "test.h"

static	void	ft_calculsprite(draws *ds, raycasting *ray)
{
	ds->spriteheight = abs((int)(ray->h / (ds->transformy)));
	ds->drawstarty = -ds->spriteheight / 2 + ray->h / 2;
	if (ds->drawstarty < 0)
		ds->drawstarty = 0;
	ds->drawendy = ds->spriteheight / 2 + ray->h / 2;
	if (ds->drawendy >= ray->h)
		ds->drawendy = ray->h - 1;
	ds->spritewidth = abs((int)(ray->h / (ds->transformy)));
	ds->drawstartx = -ds->spritewidth / 2 + ds->spritescreenx;
	if (ds->drawstartx < 0)
		ds->drawstartx = 0;
	ds->drawendx = ds->spritewidth / 2 + ds->spritescreenx;
	if (ds->drawendx >= ray->w)
		ds->drawendx = ray->w - 1;
}

static void	ft_startinitdraws(draws *ds)
{
	ds->colors = 0;
	ds->d = 0;
	ds->drawendx = 0;
	ds->drawendy = 0;
	ds->drawstartx = 0;
	ds->drawstarty = 0;
	ds->invdet = 0;
	ds->spriteheight = 0;
	ds->spritescreenx = 0;
	ds->spritewidth = 0;
	ds->spritex = 0;
	ds->spritey = 0;
	ds->stripe = 0;
	ds->texx = 0;
	ds->texy = 0;
	ds->transformx = 0;
	ds->transformy = 0;
	ds->yy = 0;
}

static	void	ft_initdraws(draws *ds, raycasting *ray, int y)
{
	ft_startinitdraws(ds);
	ds->spritex = (ray->pars->sprites[y]->x + 0.5) - ray->posx;
	ds->spritey = (ray->pars->sprites[y]->y + 0.5) - ray->posy;
	ds->invdet = 1.0 / (ray->planex * ray->diry - ray->dirx * ray->planey);
	ds->transformx = ds->invdet * (ray->diry * ds->spritex - ray->dirx * ds->spritey);
	ds->transformy = ds->invdet * (-ray->planey * ds->spritex + ray->planex * ds->spritey);
	ds->spritescreenx = ((ray->w / 2) * (1 + ds->transformx / ds->transformy));
}

void			ft_draw_sprites(raycasting *ray, int y, double *zbuffer)
{
	draws	ds;
	int		texx;
	int		d;
	int		texy;
	int		colors;
	int		stripe;
	int		yy;

	yy = 0;
	stripe = 0;
	colors = 0;
	texy = 0;
	d = 0;
	texx = 0;
	ft_initdraws(&ds, ray, y);
	ft_calculsprite(&ds, ray);
	stripe = ds.drawstartx;
	while (stripe < ds.drawendx)
	{
		texx = ((256 * (stripe - \
			(-ds.spritewidth / 2 + ds.spritescreenx)) \
				* ray->texture[4].textwidth / ds.spritewidth) / 256);
		if (texx < 0)
			texx = 1;
		if (ds.transformy > 0 && stripe > 0 \
			&& stripe < ray->w && ds.transformy < zbuffer[stripe])
		{
			yy = ds.drawstarty;
			while (yy < ds.drawendy)
			{
				d = (yy) * 256 - ray->h * 128 + ds.spriteheight * 128;
				texy = ((d * ray->texture[4].textheight) / ds.spriteheight) / 256;
				colors = ray->texture[4].imagedata[ray->texture[4].textheight \
					* texy + texx];
				if ((colors & (0xff << 24)) == 0)
					ray->imagescreenb[(ray->w) * yy + stripe] = colors;
				yy++;
			}
		}
		 stripe++;
	}
}
