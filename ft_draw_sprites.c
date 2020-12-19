/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 19:08:33 by user42            #+#    #+#             */
/*   Updated: 2020/12/19 01:27:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "test.h"

void	ft_calculsprite(draws *ds, raycasting *ray)
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

void	ft_startinitdraws(draws *ds)
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

void	drawcolors(draws *ds, raycasting *ray)
{
	while (ds->yy < ds->drawendy)
	{
		ds->d = (ds->yy) * 256 - ray->h * 128 + ds->spriteheight * 128;
		ds->texy = ((ds->d * ray->textures[4].textheight) \
		/ ds->spriteheight) / 256;
		ds->colors = \
		ray->textures[4].imagedata[ray->textures[4].textheight \
		* ds->texy + ds->texx];
		if ((ds->colors & (0xff << 24)) == 0)
			ray->imagescreenb[(ray->w) * ds->yy + ds->stripe] = ds->colors;
		ds->yy++;
	}
}

void	ft_drawspritetwo(draws *ds, raycasting *ray, double *zbuffer)
{
	ds->stripe = ds->drawstartx;
	while (ds->stripe < ds->drawendx)
	{
		ds->texx = ((256 * (ds->stripe - \
		(-ds->spritewidth / 2 + ds->spritescreenx))\
		* ray->textures[4].textwidth / ds->spritewidth) / 256);
		if (ds->texx < 0)
			ds->texx = 1;
		if (ds->transformy > 0 && ds->stripe > 0 && ds->stripe \
		< ray->w && ds->transformy < zbuffer[ds->stripe])
		{
			ds->yy = ds->drawstarty;
			drawcolors(ds, ray);
		}
		ds->stripe++;
	}
}

void	ft_draw_sprites(raycasting *ray, int y, double *zbuffer)
{
	draws ds;

	ft_initdraws(&ds, ray, y);
	ft_calculsprite(&ds, ray);
	ft_drawspritetwo(&ds, ray, zbuffer);
}
