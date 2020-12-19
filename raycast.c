/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 19:44:24 by user42            #+#    #+#             */
/*   Updated: 2020/12/19 02:25:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static void	put_pixel(int color, unsigned int *imagescreenb, int x, int y, int ratio_x, int ratio_y, int screenx)
{
	int yy;
	int xx;
	int xtmp;

	xx = 0;
	yy = 0;
	xtmp = x;
	while (yy < ratio_y)
	{
		xx = 0;
		x = xtmp;
		while (xx < ratio_x)
		{
			imagescreenb[y * screenx + x] = color;
			x++;
			xx++;
		}
		y++;
		yy++;
	}
}

static void	mini_map(raycasting *ray)
{
	mini ds;
	
	ds.ratio_x = ((ray->w / 8) - (ray->w / (16 * 2))) / ray->pars->width;
	ds.ratio_y = ((ray->h / 8) - (ray->h / (16 * 2))) / ray->pars->height;
	ds.ii = 0;
	ds.i = 0;
	ds.y = 0;
	ds.yy = 0;
	ds.sp = 0;
	while (ds.y < ray->pars->height)
	{
		ds.i = 0;
		ds.ii = 0;
		while (ds.i < ray->pars->width)
		{
			if (ds.y == (int)ray->posx && ds.i == (int)ray->posy)
			{
				ds.color = 0xfc030b;
			}
			else if (ray->pars->tab[ds.y][ds.i] != '1')
				ds.color = 0x292d2e;
			else
				ds.color = 0x33dcf2;
			while (ray->pars->sprites != NULL && ray->pars->sprites[ds.sp] != NULL)
			{
				if (ds.y == ray->pars->sprites[ds.sp]->x && ds.i == ray->pars->sprites[ds.sp]->y)
					ds.color = 0xffffff;
				ds.sp++;
			}
			put_pixel(ds.color, ray->imagescreenb, ds.ii, ds.yy, ds.ratio_x, ds.ratio_y, ray->w);
			ds.ii += ds.ratio_x;
			ds.i++;
			ds.sp = 0;
		}
		ds.yy += ds.ratio_y;
		ds.y++;
	}
}

static void	mini_life(raycasting *ray)
{
	mini mn;

	if (ray->pars->tabhud == NULL)
		return ;
	mn.ratio_x = (((ray->w / 5) - (ray->w / (16 * 2))) / ray->pars->hwidth);
	mn.ratio_y = (((ray->w / 20) - (ray->w / (16 * 2))) / ray->pars->hheight);
	mn.ii = ray->w / 3;
	mn.i = 0;
	mn.y = 0;
	mn.yy = ray->w / 30;
	while (mn.y < ray->pars->hheight)
	{
		mn.i = 0;
		mn.ii = ray->w / 3;
		while (mn.i < ray->pars->hwidth)
		{
			mn.color = 0xc21316;
			if (ray->pars->tabhud[mn.y][mn.i] == '4' || ray->pars->tabhud[mn.y][mn.i] == '6')
				put_pixel(mn.color, ray->imagescreenb, mn.ii, mn.yy, mn.ratio_x, mn.ratio_y, ray->w);
			mn.ii += mn.ratio_x;
			mn.i++;
		}
		mn.yy += mn.ratio_y;
		mn.y++;
	}
}

void	freeall(parse *pars)
{
	freepars(pars);
}

static void	init_texture(texture *textures, parse *pars, void *mlx)
{
	int fd;
	int i;

	i = 0;
	textures[0].path = pars->no;
	textures[1].path = pars->ea;
	textures[2].path = pars->we;
	textures[3].path = pars->so;
	textures[4].path = pars->s;
	fd = 0;
	while (i < 5)
	{
		if (textures[i].path == NULL)
			ft_error("ERROR OPEN FILE NULL PATH", pars);
		if ((fd = open(textures[i].path, O_RDONLY)) <= 0)
			ft_error("ERROR OPEN FILE", pars);
		close(fd);
		if ((textures[i].img = mlx_xpm_file_to_image(mlx, textures[i].path, &textures[i].textwidth, &textures[i].textheight)) == NULL)
			ft_error("Error xpm to file", pars);
		if ((textures[i].imagedata = (int *)mlx_get_data_addr(textures[i].img, &textures[i].bpp, &textures[i].size_line, &textures[i].endian)) == NULL)
			ft_error("Error xpm to file", pars);
		i++;
	}
}

static void	ft_checkun(parse *pars)
{
	if (pars->r.i == 0)
		ft_error("error resolution", pars);
	if (pars->r.ii == 0)
		ft_error("error resolution", pars);
	if (pars->c == -1 || pars->f == -1)
		ft_error("error color", pars);
}

int		main(int argc, char *argv[])
{
	parse			*pars;
	int				fdd;
	void			*screenb;
	unsigned	int	*imagescreenb;
	void			*mlx;
	int				screenx;
	int				screeny;
	int				w;
	int				h;
	void			*mlx_win;
	int				bpp;
	int				size_line;
	int				endian;
	texture			textures[5];
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planey;
	double			planex;
	int				fd;
	raycasting		param;

	fd = 0;
	if (argc >= 2)
	{
		fdd = open(argv[1], O_RDWR);
		if (fdd > 0)
			pars = cub_skip_header(fdd);
		else
		{
			ft_putstr_fd("Error open .cub file", 1);
		}
	}
	else
	{
		ft_putstr_fd("error ARG", 1);
		exit(0);
	}
	ft_checkun(pars);
	mlx = mlx_init();
	mlx_get_screen_size(mlx, &screenx, &screeny);
	if (pars->r.i > screenx)
		pars->r.i = screenx;
	if (pars->r.ii > screeny)
		pars->r.ii = screeny;
	w = pars->r.i;
	h = pars->r.ii;
	screenb = mlx_new_image(mlx, pars->r.i, pars->r.ii);
	if ((imagescreenb = (unsigned int *)mlx_get_data_addr(screenb, &bpp, &size_line, &endian)) == NULL)
		ft_putstr_fd("get data addr screen", 1);
	init_texture(textures, pars, mlx);
	posx = (float)pars->play.x;
	posy = (float)pars->play.y;
	dirx = 1.0;
	diry = 0.0;
	planex = 0.0;
	planey = -0.66;
	if (pars->play.direction == 'E')
	{
		planey = 0.0;
		planex = 0.66;
		dirx = 0.0;
		diry = 1;
	}
	if (pars->play.direction == 'W')
	{
		planey = 0.0;
		planex = -0.66;
		dirx = 0.0;
		diry = -1;
	}
	if (pars->play.direction == 'S')
	{
		planey = -0.66;
		planex = 0.0;
		dirx = 1.0;
		diry = 0.0;
	}
	if (pars->play.direction == 'N')
	{
		planey = 0.66;
		planex = 0.0;
		dirx = -1.0;
		diry = 0.0;
	}
	param.posy = posy + 0.5;
	param.posx = posx + 0.5;
	param.dirx = dirx;
	param.diry = diry;
	param.planey = planey;
	param.planex = planex;
	param.w = w;
	param.h = h;
	param.mlx = mlx;
	param.imagescreenb = imagescreenb;
	param.screenb = screenb;
	param.size_line = size_line;
	param.textures = textures;
	param.pars = pars;
	param.left = 0;
	param.right = 0;
	param.rotate_right = 0;
	param.rotate_left = 0;
	param.back = 0;
	param.forward = 0;
	param.save = 0;
	if (argc >= 3 && ft_strcmp(argv[2], "--save") == 0)
	{
		if ((fd = open("image.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 777)) > 0)
		{
			param.save = 1;
			raycast(&param);
			save_bitmap(param.imagescreenb, param.w, param.h, fd);
			freeall(pars);
			close(fd);
			exit(1);
		}
		else
			ft_error("Error create save img", pars);
	}
	mlx_win = mlx_new_window(mlx, param.w, param.h, "Rasaboun Raycasting !");
	param.mlx_win = mlx_win;
	mlx_hook(mlx_win, 2, 1L << 0, ft_key_press, &param);
	mlx_hook(mlx_win, 3, 1L << 1, ft_key_release, &param);
	mlx_loop_hook(mlx, raycast, &param);
	mlx_loop(mlx);
}

int	raycast(raycasting *ray)
{
	double	zbuffer[ray->w];
	int		i;

	i  = 0;
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
	for (int n = 0; n < (ray->w * ray->h); n++)
	{
		ray->imagescreenb[n] = 0;
	}
	for (int x = 0; x < ray->w; x++)
	{
		ft_dda(ray, x);
		ft_draw(ray, x, zbuffer);
	}
	while (ray->pars->sprites != NULL && ray->pars->sprites[i] != NULL)
		i++;
	if (i != 0)
	{
		sort_sprite(ray->pars->sprites, ray->posx, ray->posy, i);
		for (int y = 0; y < i; y++)
		{
			ft_draw_sprites(ray, y, zbuffer);
		}
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
