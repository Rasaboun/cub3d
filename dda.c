/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 05:00:13 by user42            #+#    #+#             */
/*   Updated: 2020/12/11 05:12:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "test.h"

void    dda(raycasting *ray, int x, ddas *ddavar)
{
    double camerax;
    double raydirx;
    double raydiry;
    int mapx;
    int mapy;
	double sidedistx;
	double sidedisty;
    double deltadistx;
    double deltadisty;
	double perpwalldist;
    int stepx;
	int stepy;
	int side;
    int hit;
        
        camerax = 2 * x / (double)ray->w - 1;
		raydirx = ray->dirx + ray->planex * camerax;
		raydiry = ray->diry + ray->planey * camerax;

        mapx = (int)ray->posx;
		mapy = (int)ray->posy;



		deltadistx = fabs(1 / raydirx));
		deltadisty = fabs(1 / raydiry));




		hit = 0;


		if (raydirx < 0)
		{
			stepx = -1;
			sidedistx = (ray->posx - mapx) * deltadistx;
		}
		else
		{
			stepx = 1;
			sidedistx = (mapx + 1.0 - ray->posx) * deltadistx;
		}
		if (raydiry < 0)
		{
			stepy = -1;
			sidedisty = (ray->posy - mapy) * deltadisty;
		}
		else
		{
			stepy = 1;
			sidedisty = (mapy + 1.0 - ray->posy) * deltadisty;
		}

		while (hit == 0)
		{
			if (sidedistx < sidedisty)
			{
				sidedistx += deltadistx;
				mapx += stepx;
				side = 0;
			}
			else
			{
				sidedisty += deltadisty;
				mapy += stepy;
				side = 1;
			}
			if (ray->pars->tab[mapx][mapy] == '1')
				hit = 1;
		}
		if (side == 0)
			perpwalldist = (double)(mapx - ray->posx + (1 - stepx) / 2) / raydirx;
		else
			perpwalldist = (double)(mapy - ray->posy + (1 - stepy) / 2) / raydiry;

		if (perpwalldist <= 0.0)
		{
			perpwalldist = 1;

		}
}