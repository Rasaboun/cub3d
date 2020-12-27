/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 01:26:20 by user42            #+#    #+#             */
/*   Updated: 2020/12/27 20:31:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test.h"
#include "../libft/libft.h"
#include "../get_next_line.h"
#include "../raycast.h"

void			freeall(t_parse *pars)
{
	freepars(pars);
}

void			intextpath(t_texture *textures, t_parse *pars)
{
	textures[0].path = pars->no;
	textures[1].path = pars->ea;
	textures[2].path = pars->we;
	textures[3].path = pars->so;
	textures[4].path = pars->s;
	textures[0].img = NULL;
	textures[1].img = NULL;
	textures[2].img = NULL;
	textures[3].img = NULL;
	textures[4].img = NULL;
}

void			init_texture(t_texture *tex, t_raycasting *ray, void *mlx)
{
	int fd;
	int i;

	i = 0;
	intextpath(tex, ray->pars);
	fd = 0;
	while (i < 5)
	{
		if (tex[i].path == NULL)
			ft_errorescape("Error open tex file", ray);
		if ((fd = open(tex[i].path, O_RDONLY)) <= 0)
			ft_errorescape("Error open tex file", ray);
		close(fd);
		if ((tex[i].img = mlx_xpm_file_to_image(mlx,
			tex[i].path, &tex[i].textwidth,
			&tex[i].textheight)) == NULL)
			ft_errorescape("Error xpm to file", ray);
		if ((tex[i].imagedata =
			(int *)mlx_get_data_addr(tex[i].img,
			&tex[i].bpp, &tex[i].size_line, &tex[i].endian)) == NULL)
			ft_errorescape("Error xpm to file", ray);
		i++;
	}
}

void			ft_checkun(t_parse *pars)
{
	if (pars->r.i == 0)
		ft_error("error resolution", pars);
	if (pars->r.ii == 0)
		ft_error("error resolution", pars);
	if (pars->c == -1 || pars->f == -1)
		ft_error("error color", pars);
}

void			initcub(t_raycasting *param, t_parse *pars, t_texture *textures)
{
	param->textures = textures;
	param->posy = (float)pars->play.y + 0.5;
	param->posx = (float)pars->play.x + 0.5;
	param->left = 0;
	param->right = 0;
	param->rotate_right = 0;
	param->rotate_left = 0;
	param->back = 0;
	param->forward = 0;
	param->save = 0;
	param->pars = pars;
}
