/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycastchoose.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 01:27:44 by user42            #+#    #+#             */
/*   Updated: 2023/03/14 14:03:26 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include "../libft/libft.h"
#include "../include/get_next_line.h"
#include "../include/raycast.h"

void	chooseplayerdirtwo(t_raycasting *ray, t_parse *pars)
{
	if (pars->play.direction == 'E')
	{
		ray->planey = 0.0;
		ray->planex = 0.66;
		ray->dirx = 0.0;
		ray->diry = 1;
	}
	if (pars->play.direction == 'W')
	{
		ray->planey = 0.0;
		ray->planex = -0.66;
		ray->dirx = 0.0;
		ray->diry = -1;
	}
}

void	chooseplayerdir(t_raycasting *ray, t_parse *pars)
{
	chooseplayerdirtwo(ray, pars);
	if (pars->play.direction == 'S')
	{
		ray->planey = -0.66;
		ray->planex = 0.0;
		ray->dirx = 1.0;
		ray->diry = 0.0;
	}
	if (pars->play.direction == 'N')
	{
		ray->planey = 0.66;
		ray->planex = 0.0;
		ray->dirx = -1.0;
		ray->diry = 0.0;
	}
}

void	argsave(int argc, char **argv, t_raycasting *param, t_parse *pars)
{
	int fd;

	fd = 0;
	if (argc == 3 && ft_strcmp(argv[2], "--save") == 0)
	{
		if ((fd = open("image.bmp", O_WRONLY | \
		O_CREAT | O_TRUNC | O_APPEND, 777)) > 0)
		{
			param->save = 1;
			raycast(param);
			save_bitmap(param->imagescreenb, param->w, param->h, fd);
			close(fd);
			escape(param);
		}
		else
			ft_errorescape("Error create save img", param);
	}
}

void	max_reso(t_parse *pars, t_raycasting *param, int sx, int sy)
{
	if (pars->r.i <= 0 || pars->r.ii <= 0)
		ft_error("Negatif resolution", pars);
	if (pars->r.i > sx)
		pars->r.i = sx;
	if (pars->r.ii > sy)
		pars->r.ii = sy;
	param->w = pars->r.i;
	param->h = pars->r.ii;
}

t_parse	*check_arg(int argc, char **av)
{
	int fd;
	int n;

	fd = 0;
	n = 0;
	if (argc == 3 && ft_strcmp(av[2], "--save") != 0)
		ft_error("error arg save", NULL);
	if (argc <= 3 && argc >= 2)
	{
		n = ft_strlen(av[1]);
		if (n > 4 && av[1][n - 1] == 'b' &&
			av[1][n - 2] == 'u' && av[1][n - 3] == 'c' && av[1][n - 4] == '.')
		{
			fd = open(av[1], O_RDWR);
			if (fd > 0)
				return (cub_skip_header(fd));
			else
				ft_error("Error open .cub file", NULL);
		}
		else
			ft_error("error not .cub", NULL);
	}
	else
		ft_error("error arg", NULL);
	return (NULL);
}
