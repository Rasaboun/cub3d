/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 19:32:59 by user42            #+#    #+#             */
/*   Updated: 2023/03/14 14:03:07 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include "../libft/libft.h"
#include "../include/get_next_line.h"
#include "../include/raycast.h"

void	initparam(t_raycasting *param, t_texture *textures)
{
	param->mlx_win = NULL;
	param->mlx = NULL;
	param->imagescreenb = NULL;
	param->screenb = NULL;
	param->textures = NULL;
}

void	inittexture(t_texture *tex, t_raycasting *param)
{
	param->textures = tex;
	init_texture(param->textures, param, param->mlx);
}
