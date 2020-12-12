/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 05:00:13 by user42            #+#    #+#             */
/*   Updated: 2020/12/12 18:32:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "test.h"

void    ft_dda(raycasting *ray, int x)
{
    double camerax;
	double sidedistx;
	double sidedisty;
    double deltadistx;
    double deltadisty;
    int stepx;
	int stepy;
    int hit;
        
        camerax = 2 * x / (double)ray->w - 1;
		ray->raydirx = ray->dirx + ray->planex * camerax;
		ray->raydiry = ray->diry + ray->planey * camerax;

        ray->mapx = (int)ray->posx;
		ray->mapy = (int)ray->posy;



		deltadistx = fabs(1 / ray->raydirx);
		deltadisty = fabs(1 / ray->raydiry);




		hit = 0;


		if (ray->raydirx < 0)
		{
			stepx = -1;
			sidedistx = (ray->posx - ray->mapx) * deltadistx;
		}
		else
		{
			stepx = 1;
			sidedistx = (ray->mapx + 1.0 - ray->posx) * deltadistx;
		}
		if (ray->raydiry < 0)
		{
			stepy = -1;
			sidedisty = (ray->posy - ray->mapy) * deltadisty;
		}
		else
		{
			stepy = 1;
			sidedisty = (ray->mapy + 1.0 - ray->posy) * deltadisty;
		}

		while (hit == 0)
		{
			if (sidedistx < sidedisty)
			{
				sidedistx += deltadistx;
				ray->mapx += stepx;
				ray->side = 0;
			}
			else
			{
				sidedisty += deltadisty;
				ray->mapy += stepy;
				ray->side = 1;
			}
			if (ray->pars->tab[ray->mapx][ray->mapy] == '1')
				hit = 1;
		}
		if (ray->side == 0)
			ray->perpwalldist = (double)(ray->mapx - ray->posx + (1 - stepx) / 2) / ray->raydirx;
		else
			ray->perpwalldist = (double)(ray->mapy - ray->posy + (1 - stepy) / 2) / ray->raydiry;

		if (ray->perpwalldist <= 0.0)
		{
			ray->perpwalldist = 1;
		}
}