/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 05:14:19 by user42            #+#    #+#             */
/*   Updated: 2020/12/12 19:38:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "test.h"

void    ft_draw(raycasting *ray, int x,double *zbuffer)
{
        int lineHeight = (int)(ray->h / ray->perpwalldist);
		int drawStart = -lineHeight / 2 + ray->h / 2;

		if (drawStart < 0)
			drawStart = 0;

		int drawEnd = lineHeight / 2 + ray->h / 2;

		if (drawEnd >= ray->h)
			drawEnd = ray->h - 1;
		int charint = (ray->pars->tab[ray->mapx][ray->mapy] - 48);
		int texNum = charint - 1;
		double wallX;

		if (ray->side == 0)
			wallX = ray->posy + ray->perpwalldist * ray->raydiry;
		else
			wallX = ray->posx + ray->perpwalldist * ray->raydirx;

		if (ray->side == 0 && ray->raydirx > 0)
			ray->side = 3;
		if (ray->side == 1 && ray->raydiry < 0)
			ray->side = 2;
		wallX -= floor((wallX));
		int texX = (int)(wallX * (double)(ray->texture[ray->side].textwidth));

		if (ray->side == 0)
			texX = ray->texture[ray->side].textwidth - texX - 1;
		if (ray->side == 1)
			texX = ray->texture[ray->side].textwidth - texX - 1;

		double step = 1.0 * ray->texture[ray->side].textwidth / lineHeight;
		double texPos = (drawStart - ray->h / 2 + lineHeight / 2) * step;

		for (int begin = 0; begin < drawStart; begin++)
		{
			ray->imagescreenb[(ray->w)*begin + x] = ray->pars->c;
		}

		for (int end = drawEnd; end < ray->h; end++)
		{
			ray->imagescreenb[(ray->w)*end + x] = ray->pars->f;
		}
		for (int y = drawStart; y < drawEnd; y++)
		{
			int texY = (int)texPos & (ray->texture[ray->side].textheight - 1);

			texPos += step;
			int color = ray->texture[ray->side].imagedata[ray->texture[ray->side].textheight * texY + ray->texture[ray->side].textwidth - texX];
				ray->imagescreenb[(ray->w)*y + x] = color;
		}
		zbuffer[x] = ray->perpwalldist;


}