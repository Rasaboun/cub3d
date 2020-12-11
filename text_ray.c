/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 05:14:19 by user42            #+#    #+#             */
/*   Updated: 2020/12/11 05:15:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "test.h"

void    text_ray(raycasting *ray, int x)
{
        int lineHeight = (int)(ray->h / perpwalldist);
		int drawStart = -lineHeight / 2 + ray->h / 2;

		if (drawStart < 0)
			drawStart = 0;

		int drawEnd = lineHeight / 2 + ray->h / 2;

		if (drawEnd >= ray->h)
			drawEnd = ray->h - 1;
		int charint = (ray->pars->tab[mapx][mapy] - 48);
		int texNum = charint - 1;
		double wallX;

		if (side == 0)
			wallX = ray->posy + perpwalldist * raydiry;
		else
			wallX = ray->posx + perpwalldist * raydirx;

		if (side == 0 && raydirx > 0)
			side = 3;
		if (side == 1 && raydiry < 0)
			side = 2;
		wallX -= floor((wallX));
		int texX = (int)(wallX * (double)(ray->texture[side].textwidth));

		if (side == 0)
			texX = ray->texture[side].textwidth - texX - 1;
		if (side == 1)
			texX = ray->texture[side].textwidth - texX - 1;

		double step = 1.0 * ray->texture[side].textwidth / lineHeight;
		double texPos = (drawStart - ray->h / 2 + lineHeight / 2) * step;

		for (int begin = 0; begin < drawStart; begin++)
		{
			ray->imagescreenB[(ray->w)*begin + x] = ray->pars->c;
		}

		for (int end = drawEnd; end < ray->h; end++)
		{
			ray->imagescreenB[(ray->w)*end + x] = ray->pars->f;
		}
		for (int y = drawStart; y < drawEnd; y++)
		{
			int texY = (int)texPos & (ray->texture[side].textheight - 1);

			texPos += step;
			int color = ray->texture[side].imagedata[ray->texture[side].textheight * texY + ray->texture[side].textwidth - texX];
				ray->imagescreenB[(ray->w)*y + x] = color;
		}
		zbuffer[x] = perpwalldist;


}