/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 04:21:56 by user42            #+#    #+#             */
/*   Updated: 2020/12/12 20:18:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "test.h"

 void    move_forward(raycasting *ray)
{
	if (ray->pars->tab[(int)(ray->posx + ray->dirx * 0.02)][(int)ray->posy] == '0')
		ray->posx += ray->dirx * 0.02;
	if (ray->pars->tab[(int)ray->posx][(int)(ray->posy + ray->diry * 0.02)] == '0')
		ray->posy += ray->diry * 0.02;
}

 void    move_back(raycasting *ray)
{
	if (ray->pars->tab[(int)(ray->posx - ray->dirx * 0.02)][(int)ray->posy] == '0')
		ray->posx -= ray->dirx * 0.02;
	if (ray->pars->tab[(int)ray->posx][(int)(ray->posy - ray->diry * 0.02)] == '0')
		ray->posy -= ray->diry * 0.02;
}

 void    move_right(raycasting *ray)
{
	if (ray->pars->tab[(int)ray->posx][(int)(ray->posy + ray->planey * 0.02)] == '0')
		ray->posy += ray->planey * 0.02;
	if (ray->pars->tab[(int)(ray->posx + ray->planex * 0.02)][(int)ray->posy] == '0')
		ray->posx += ray->planex * 0.02;
}

 void    move_left(raycasting *ray)
{
	if (ray->pars->tab[(int)ray->posx][(int)(ray->posy - ray->planey * 0.02)] == '0')
		ray->posy -= ray->planey * 0.02;
	if (ray->pars->tab[(int)(ray->posx - ray->planex * 0.02)][(int)ray->posy] == '0')
		ray->posx -= ray->planex * 0.02;
}

 void    turn_left(raycasting *ray)
{
	double olddirx;
    double oldplanex;
    
    oldplanex = ray->planex;
    olddirx = ray->dirx;
	ray->dirx = ray->dirx * cos(0.02) - ray->diry * sin(0.02);
	ray->diry = olddirx * sin(0.02) + ray->diry * cos(0.02);
	ray->planex = ray->planex * cos(0.02) - ray->planey * sin(0.02);
	ray->planey = oldplanex * sin(0.02) + ray->planey * cos(0.02);
}

 void    turn_right(raycasting *ray)
{
		double olddirx;
		double oldplanex;

        olddirx = ray->dirx;
        oldplanex = ray->planex;
		ray->dirx = ray->dirx * cos(-0.02) - ray->diry * sin(-0.02);
		ray->diry = olddirx * sin(-0.02) + ray->diry * cos(-0.02);
		ray->planex = ray->planex * cos(-0.02) - ray->planey * sin(-0.02);
		ray->planey = oldplanex * sin(-0.02) + ray->planey * cos(-0.02);
}

static void    escape(raycasting *ray)
{
    int fdd;
 
	fdd = 0;
	fdd = open("image.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 777);
	if (fdd > 0 && ray->save == 1)
		save_bitmap(ray->imagescreenb, ray->w, ray->h, fdd);
	mlx_destroy_window(ray->mlx, ray->mlx_win);
	freeall(ray->pars);
	exit(EXIT_SUCCESS);
}

int ft_key_press(int key, void *param)
{
	raycasting *ray = (raycasting *)param;

	if (key == 	97)
        ray->left = 1;
	if (key == 	100)
        ray->right = 1;
	if (key == 119)
        ray->forward = 1;
	if (key == 	115)
        ray->back = 1;
	if (key == 65363)
        ray->rotate_right = 1;
	if (key == 65361)
        ray->rotate_left = 1;
	if (key == 65307)
        escape(ray);
	return 1;
}

int ft_key_release(int key, void *param)
{
	raycasting *ray = (raycasting *)param;

	if (key == 	97)
        ray->left = 0;
	if (key == 	100)
        ray->right = 0;
	if (key == 119)
        ray->forward = 0;
	if (key == 	115)
        ray->back = 0;
	if (key == 65363)
        ray->rotate_right = 0;
	if (key == 65361)
        ray->rotate_left = 0;
	if (key == 65307)
        escape(ray);
	return 1;
}