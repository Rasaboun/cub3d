/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 23:05:03 by rasaboun          #+#    #+#             */
/*   Updated: 2020/12/27 21:01:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	ft_error(char *str, t_parse *pars)
{
	if (pars != NULL)
		freeall(pars);
	ft_putstr_fd(str, 1);
	exit(EXIT_FAILURE);
}

void	ft_errord(char *str, t_parse *pars, char *line)
{
	if (pars != NULL)
		freeall(pars);
	if (line != NULL)
		free(line);
	ft_putstr_fd(str, 1);
	exit(EXIT_FAILURE);
}

void	ft_errorescape(char *str, t_raycasting *ray)
{
	if (ray->pars)
		freeall(ray->pars);
	if (ray->screenb)
		mlx_destroy_image(ray->mlx, ray->screenb);
	if (ray->textures && ray->textures[0].img)
		mlx_destroy_image(ray->mlx, ray->textures[0].img);
	if (ray->textures && ray->textures[1].img)
		mlx_destroy_image(ray->mlx, ray->textures[1].img);
	if (ray->textures && ray->textures[2].img)
		mlx_destroy_image(ray->mlx, ray->textures[2].img);
	if (ray->textures && ray->textures[3].img)
		mlx_destroy_image(ray->mlx, ray->textures[3].img);
	if (ray->textures && ray->textures[4].img)
		mlx_destroy_image(ray->mlx, ray->textures[4].img);
	if (ray->mlx_win)
		mlx_destroy_window(ray->mlx, ray->mlx_win);
	if (ray->mlx)
	{
		mlx_destroy_display(ray->mlx);
		free(ray->mlx);
	}
	ft_putstr_fd(str, 1);
	exit(EXIT_FAILURE);
}

int		ft_errorcheckmap(t_checkmap *ck, t_list *lst)
{
	t_list *new;

	new = NULL;
	while (lst != NULL)
	{
		new = lst->next;
		free(lst->content);
		free(lst);
		lst = new;
	}
	return (0);
}
