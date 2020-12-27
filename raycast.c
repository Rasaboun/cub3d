/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 19:44:24 by user42            #+#    #+#             */
/*   Updated: 2020/12/27 19:36:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void			cubmlx(void *mlx_win, void *mlx, t_raycasting *param)
{
	mlx_hook(mlx_win, 33, 1L << 17, escape, param);
	mlx_hook(mlx_win, 2, 1L << 0, ft_key_press, param);
	mlx_loop_hook(mlx, raycast, param);
	mlx_hook(mlx_win, 3, 1L << 1, ft_key_release, param);
	mlx_loop(mlx);
}

int				main(int argc, char *argv[])
{
	t_parse			*pars;
	t_mains			m;
	t_texture		textures[5];
	t_raycasting	pm;

	initparam(&pm, textures);
	pars = NULL;
	pm.pars = check_arg(argc, argv);
	ft_checkun(pm.pars);
	if ((pm.mlx = mlx_init()) == NULL)
		ft_error("Error mlx init", pm.pars);
	mlx_get_screen_size(pm.mlx, &m.screenx, &m.screeny);
	max_reso(pm.pars, &pm, m.screenx, m.screeny);
	if (!(pm.screenb = mlx_new_image(pm.mlx, pm.pars->r.i, pm.pars->r.ii)))
		ft_errorescape("error new img", &pm);
	if ((pm.imagescreenb = (unsigned int *)mlx_get_data_addr(pm.screenb,\
	&m.bpp, &m.size_line, &m.endian)) == NULL)
		ft_errorescape("error get data addr screen", &pm);
	chooseplayerdir(&pm, pm.pars);
	initcub(&pm, pm.pars, textures);
	inittexture(textures, &pm);
	argsave(argc, argv, &pm, pm.pars);
	if ((pm.mlx_win = mlx_new_window(pm.mlx, pm.w, pm.h, "Cub3d")) == NULL)
		ft_errorescape("error new window", &pm);
	cubmlx(pm.mlx_win, pm.mlx, &pm);
}

void			movefunc(t_raycasting *ray)
{
	if (ray->right == 1)
		move_right(ray);
	if (ray->left == 1)
		move_left(ray);
	if (ray->back == 1)
		move_back(ray);
	if (ray->forward == 1)
		move_forward(ray);
	if (ray->rotate_left == 1)
		turn_left(ray);
	if (ray->rotate_right == 1)
		turn_right(ray);
}

void			raycastwo(t_raycasting *ray, double *zbuffer)
{
	int n;
	int x;

	x = 0;
	n = 0;
	movefunc(ray);
	while (n < (ray->w * ray->h))
	{
		ray->imagescreenb[n] = 0;
		n++;
	}
	while (x < ray->w)
	{
		ft_dda(ray, x);
		ft_draw(ray, x, zbuffer);
		x++;
	}
}

int				raycast(t_raycasting *ray)
{
	double	zbuffer[ray->w];
	int		i;
	int		y;

	y = 0;
	i = 0;
	raycastwo(ray, zbuffer);
	while (ray->pars->sprites != NULL && ray->pars->sprites[i] != NULL)
		i++;
	if (i != 0)
		sort_sprite(ray->pars->sprites, ray->posx, ray->posy, i);
	while (y < i)
	{
		ft_draw_sprites(ray, y, zbuffer);
		y++;
	}
	mini_map(ray);
	mini_life(ray);
	if (ray->save == 0)
	{
		mlx_clear_window(ray->mlx, ray->mlx_win);
		mlx_put_image_to_window(ray->mlx, ray->mlx_win, ray->screenb, 0, 0);
	}
	return (1);
}
