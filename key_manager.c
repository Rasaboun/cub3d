/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 04:21:56 by user42            #+#    #+#             */
/*   Updated: 2020/12/11 04:44:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "test.h"

static void    move_forward(raycasting *ray)
{
	if (ray->pars->tab[(int)(ray->posx + ray->dirx * 0.10)][(int)ray->posy] == '0')
		ray->posx += ray->dirx * 0.10;
	if (ray->pars->tab[(int)ray->posx][(int)(ray->posy + ray->diry * 0.10)] == '0')
		ray->posy += ray->diry * 0.10;
}

static void    move_back(raycasting *ray)
{
	if (ray->pars->tab[(int)(ray->posx - ray->dirx * 0.10)][(int)ray->posy] == '0')
		ray->posx -= ray->dirx * 0.10;
	if (ray->pars->tab[(int)ray->posx][(int)(ray->posy - ray->diry * 0.10)] == '0')
		ray->posy -= ray->diry * 0.10;
}

static void    move_right(raycasting *ray)
{
	if (ray->pars->tab[(int)ray->posx][(int)(ray->posy + ray->planey * 0.10)] == '0')
		ray->posy += ray->planey * 0.10;
	if (ray->pars->tab[(int)(ray->posx + ray->planex * 0.10)][(int)ray->posy] == '0')
		ray->posx += ray->planex * 0.10;
}

static void    move_left(raycasting *ray)
{
	if (ray->pars->tab[(int)ray->posx][(int)(ray->posy - ray->planey * 0.10)] == '0')
		ray->posy -= ray->planey * 0.10;
	if (ray->pars->tab[(int)(ray->posx - ray->planex * 0.10)][(int)ray->posy] == '0')
		ray->posx -= ray->planex * 0.10;
}

static void    turn_left(raycasting *ray)
{
	double olddirx;
    double oldplanex;
    
    oldplanex = ray->planex;
    olddirx = ray->dirx;
	ray->dirx = ray->dirx * cos(0.10) - ray->diry * sin(0.10);
	ray->diry = olddirx * sin(0.10) + ray->diry * cos(0.10);
	ray->planex = ray->planex * cos(0.10) - ray->planey * sin(0.10);
	ray->planey = oldplanex * sin(0.10) + ray->planey * cos(0.10);
}

static void    turn_right(raycasting *ray)
{
		double olddirx;
		double oldplanex;

        olddirx = ray->dirx;
        oldplanex = ray->planex;
		ray->dirx = ray->dirx * cos(-0.10) - ray->diry * sin(-0.10);
		ray->diry = olddirx * sin(-0.10) + ray->diry * cos(-0.10);
		ray->planex = ray->planex * cos(-0.10) - ray->planey * sin(-0.10);
		ray->planey = oldplanex * sin(-0.10) + ray->planey * cos(-0.10);
}

static void    escape(raycasting *ray)
{
    int fdd;
 
	fdd = 0;
	fdd = open("image.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 777);
	if (fdd > 0 && ray->save == 1)
		save_bitmap(ray->imagescreenB, ray->w, ray->h, fdd);
	mlx_destroy_window(ray->mlx, ray->mlx_win);
	freeall(ray->pars);
	exit(EXIT_SUCCESS);
}

int deal_key(int key, void *param)
{
	raycasting *ray = (raycasting *)param;
	mlx_clear_window(ray->mlx, ray->mlx_win);

	if (key == 	97)
        move_left(ray);
	if (key == 	100)
        move_right(ray);
	if (key == 119)
        move_forward(ray);
	if (key == 	115)
        move_back(ray);
	if (key == 65363)
        turn_right(ray);
	if (key == 65361)
        turn_left(ray);
	if (key == 65307)
        escape(ray);
	return 1;
}