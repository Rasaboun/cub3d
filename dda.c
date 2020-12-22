/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 05:00:13 by user42            #+#    #+#             */
/*   Updated: 2020/12/22 01:01:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "test.h"

void	initdda(t_ddas *dd, t_raycasting *ray, int x)
{
	dd->camerax = 2 * x / (double)ray->w - 1;
	ray->raydirx = ray->dirx + ray->planex * dd->camerax;
	ray->raydiry = ray->diry + ray->planey * dd->camerax;
	ray->mapx = (int)ray->posx;
	ray->mapy = (int)ray->posy;
	dd->deltadistx = fabs(1 / ray->raydirx);
	dd->deltadisty = fabs(1 / ray->raydiry);
	dd->hit = 0;
}

void	choosedir(t_raycasting *ray, t_ddas *dd)
{
	if (ray->raydirx < 0)
	{
		dd->stepx = -1;
		dd->sidedistx = (ray->posx - ray->mapx) * dd->deltadistx;
	}
	else
	{
		dd->stepx = 1;
		dd->sidedistx = (ray->mapx + 1.0 - ray->posx) * dd->deltadistx;
	}
	if (ray->raydiry < 0)
	{
		dd->stepy = -1;
		dd->sidedisty = (ray->posy - ray->mapy) * dd->deltadisty;
	}
	else
	{
		dd->stepy = 1;
		dd->sidedisty = (ray->mapy + 1.0 - ray->posy) * dd->deltadisty;
	}
}

void	findhit(t_raycasting *ray, t_ddas *dd)
{
	while (dd->hit == 0)
	{
		if (dd->sidedistx < dd->sidedisty)
		{
			dd->sidedistx += dd->deltadistx;
			ray->mapx += dd->stepx;
			ray->side = 0;
		}
		else
		{
			dd->sidedisty += dd->deltadisty;
			ray->mapy += dd->stepy;
			ray->side = 1;
		}
		if (ray->pars->tab[ray->mapx][ray->mapy] == '1')
			dd->hit = 1;
	}
}

void	ft_dda(t_raycasting *ray, int x)
{
	t_ddas dd;

	initdda(&dd, ray, x);
	choosedir(ray, &dd);
	findhit(ray, &dd);
	if (ray->side == 0)
		ray->perpwalldist = (double)(ray->mapx - \
		ray->posx + (1 - dd.stepx) / 2) / ray->raydirx;
	else
		ray->perpwalldist = (double)(ray->mapy - \
		ray->posy + (1 - dd.stepy) / 2) / ray->raydiry;
	if (ray->perpwalldist <= 0.0)
	{
		ray->perpwalldist = 1;
	}
}
