/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 05:14:19 by user42            #+#    #+#             */
/*   Updated: 2020/12/22 01:00:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "test.h"

void	ft_drawtwo(t_draws *draw, t_raycasting *ray)
{
	draw->lineheight = (int)(ray->h / ray->perpwalldist);
	draw->drawstart = -draw->lineheight / 2 + ray->h / 2;
	if (draw->drawstart < 0)
		draw->drawstart = 0;
	draw->drawend = draw->lineheight / 2 + ray->h / 2;
	if (draw->drawend >= ray->h)
		draw->drawend = ray->h - 1;
	draw->charint = (ray->pars->tab[ray->mapx][ray->mapy] - 48);
	draw->texnum = draw->charint - 1;
}

void	ft_drawthree(t_draws *draw, t_raycasting *ray, int x)
{
	int		begin;

	begin = -1;
	if (ray->side == 0)
		draw->wallx = ray->posy + ray->perpwalldist * ray->raydiry;
	else
		draw->wallx = ray->posx + ray->perpwalldist * ray->raydirx;
	if (ray->side == 0 && ray->raydirx > 0)
		ray->side = 3;
	if (ray->side == 1 && ray->raydiry < 0)
		ray->side = 2;
	draw->wallx -= floor((draw->wallx));
	draw->texx = (int)(draw->wallx * \
	(double)(ray->textures[ray->side].textwidth));
	if (ray->side == 0)
		draw->texx = ray->textures[ray->side].textwidth - draw->texx - 1;
	if (ray->side == 1)
		draw->texx = ray->textures[ray->side].textwidth - draw->texx - 1;
	draw->step = 1.0 * ray->textures[ray->side].textwidth \
	/ draw->lineheight;
	draw->texpos = (draw->drawstart - \
	ray->h / 2 + draw->lineheight / 2) * draw->step;
	while (begin++ < draw->drawstart)
		ray->imagescreenb[(ray->w) * begin + x] = ray->pars->c;
}

void	ft_draw(t_raycasting *ray, int x, double *zbuffer)
{
	t_draws	draw;
	int		end;
	int		y;
	int		color;

	color = 0;
	ft_drawtwo(&draw, ray);
	ft_drawthree(&draw, ray, x);
	end = draw.drawend - 1;
	while (end++ < ray->h)
		ray->imagescreenb[(ray->w) * end + x] = ray->pars->f;
	y = draw.drawstart - 1;
	while (y++ < draw.drawend)
	{
		draw.texy = (int)draw.texpos \
		& (ray->textures[ray->side].textheight - 1);
		draw.texpos += draw.step;
		color = \
		ray->textures[ray->side].imagedata[ray->textures[ray->side].textheight \
		* draw.texy + ray->textures[ray->side].textwidth - draw.texx];
		ray->imagescreenb[(ray->w) * y + x] = color;
	}
	zbuffer[x] = ray->perpwalldist;
}
