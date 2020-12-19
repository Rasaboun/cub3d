/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 04:21:56 by user42            #+#    #+#             */
/*   Updated: 2020/12/19 01:47:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "test.h"

void	turn_right(raycasting *ray)
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

void	escape(raycasting *ray)
{
	mlx_destroy_window(ray->mlx, ray->mlx_win);
	freeall(ray->pars);
	exit(EXIT_SUCCESS);
}

int		ft_key_press(int key, void *param)
{
	raycasting *ray;

	ray = (raycasting *)param;
	if (key == 97)
		ray->left = 1;
	if (key == 100)
		ray->right = 1;
	if (key == 119)
		ray->forward = 1;
	if (key == 115)
		ray->back = 1;
	if (key == 65363)
		ray->rotate_right = 1;
	if (key == 65361)
		ray->rotate_left = 1;
	if (key == 65307)
		escape(ray);
	return (1);
}

int		ft_key_release(int key, void *param)
{
	raycasting *ray;

	ray = (raycasting *)param;
	if (key == 97)
		ray->left = 0;
	if (key == 100)
		ray->right = 0;
	if (key == 119)
		ray->forward = 0;
	if (key == 115)
		ray->back = 0;
	if (key == 65363)
		ray->rotate_right = 0;
	if (key == 65361)
		ray->rotate_left = 0;
	if (key == 65307)
		escape(ray);
	return (1);
}
