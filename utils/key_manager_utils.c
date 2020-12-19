/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_manager_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 01:46:36 by user42            #+#    #+#             */
/*   Updated: 2020/12/19 01:47:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test.h"
#include "../libft/libft.h"
#include "../get_next_line.h"
#include "../raycast.h"

void	move_forward(raycasting *ray)
{
	if (ray->pars->tab[(int)(ray->posx + ray->dirx *
											0.05)][(int)ray->posy] == '0')
		ray->posx += ray->dirx * 0.05;
	if (ray->pars->tab[(int)ray->posx][(int)(ray->posy\
	+ ray->diry * 0.05)] == '0')
		ray->posy += ray->diry * 0.05;
}

void	move_back(raycasting *ray)
{
	if (ray->pars->tab[(int)(ray->posx - ray->dirx *
											0.05)][(int)ray->posy] == '0')
		ray->posx -= ray->dirx * 0.05;
	if (ray->pars->tab[(int)ray->posx][(int)(ray->posy\
	- ray->diry * 0.05)] == '0')
		ray->posy -= ray->diry * 0.05;
}

void	move_right(raycasting *ray)
{
	if (ray->pars->tab[(int)ray->posx][(int)(ray->posy\
	+ ray->planey * 0.05)] == '0')
		ray->posy += ray->planey * 0.05;
	if (ray->pars->tab[(int)(ray->posx + ray->planex\
	* 0.05)][(int)ray->posy] == '0')
		ray->posx += ray->planex * 0.05;
}

void	move_left(raycasting *ray)
{
	if (ray->pars->tab[(int)ray->posx][(int)(ray->posy\
	- ray->planey * 0.05)] == '0')
		ray->posy -= ray->planey * 0.05;
	if (ray->pars->tab[(int)(ray->posx - ray->planex\
	* 0.05)][(int)ray->posy] == '0')
		ray->posx -= ray->planex * 0.05;
}

void	turn_left(raycasting *ray)
{
	double olddirx;
	double oldplanex;

	oldplanex = ray->planex;
	olddirx = ray->dirx;
	ray->dirx = ray->dirx * cos(0.04) - ray->diry * sin(0.04);
	ray->diry = olddirx * sin(0.04) + ray->diry * cos(0.04);
	ray->planex = ray->planex * cos(0.04) - ray->planey * sin(0.04);
	ray->planey = oldplanex * sin(0.04) + ray->planey * cos(0.04);
}