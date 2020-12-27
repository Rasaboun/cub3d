/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 19:32:59 by user42            #+#    #+#             */
/*   Updated: 2020/12/27 20:31:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test.h"
#include "../libft/libft.h"
#include "../get_next_line.h"
#include "../raycast.h"

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
