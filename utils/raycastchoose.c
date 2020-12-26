/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycastchoose.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 01:27:44 by user42            #+#    #+#             */
/*   Updated: 2020/12/26 19:20:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test.h"
#include "../libft/libft.h"
#include "../get_next_line.h"
#include "../raycast.h"

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
	if (argc >= 3 && ft_strcmp(argv[2], "--save") == 0)
	{
		if ((fd = open("image.bmp", O_WRONLY | \
		O_CREAT | O_TRUNC | O_APPEND, 777)) > 0)
		{
			param->save = 1;
			raycast(param);
			save_bitmap(param->imagescreenb, param->w, param->h, fd);
			freeall(pars);
			close(fd);
			exit(1);
		}
		else
			ft_error("Error create save img", pars);
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

t_parse	*check_arg(int argc, char **argv)
{
	int fd;
	int n;

	fd = 0;
	n = 0;
	n = ft_strlen(argv[1]);
	if (n > 4 && argv[1][n - 1] == 'b' && \
	argv[1][n - 2] == 'u' && argv[1][n - 3] == 'c' && argv[1][n - 4] == '.')
	{
		if (argc == 2)
		{
			fd = open(argv[1], O_RDWR);
			if (fd > 0)
				return (cub_skip_header(fd));
			else
				ft_error("Error open .cub file", NULL);
		}
		else
			ft_error("error arg", NULL);
	}
	else
		ft_error("error not .cub", NULL);
	return (NULL);
}
