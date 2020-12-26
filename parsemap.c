/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsemap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:31:18 by rasaboun          #+#    #+#             */
/*   Updated: 2020/12/26 19:09:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "libft/libft.h"
#include "get_next_line.h"
#include "raycast.h"

int		close_map(t_parse *pars, int i, int j)
{
	int linecount;

	linecount = 0;
	while (pars->tab[linecount])
		linecount++;
	if (i == 0 || i == linecount - 1 ||
		j == 0 || j == (int)ft_strlen(pars->tab[i]) - 1)
		return (0);
	if (pars->tab[i + 1][j] == ' ' || pars->tab[i - 1][j] == ' ' ||
		pars->tab[i][j + 1] == ' ' || pars->tab[i][j - 1] == ' ')
		return (0);
	if (pars->tab[i + 1][j] == '\0' || pars->tab[i - 1][j] == '\0' ||
		pars->tab[i][j + 1] == '\0' || pars->tab[i][j - 1] == '\0')
		return (0);
	return (1);
}

int		checkmap(t_parse *pars, t_list **lst)
{
	t_checkmap	ck;

	ck.play = NULL;
	ck.mapf = '\0';
	ck.player = 0;
	ck.linecount = 0;
	ck.i = 0;
	ck.j = 0;
	while (pars->tab[ck.linecount])
		ck.linecount++;
	while (ck.i < ck.linecount)
	{
		ck.j = 0;
		while (pars->tab[ck.i][ck.j])
		{
			if (ft_getelemmap(pars, &ck, lst) == 0)
				return (0);
			ck.j++;
		}
		ck.i++;
	}
	if (ck.player != 1)
		return (0);
	return (1);
}

void	get_map(int fd, t_cub_skip *map_pars)
{
	int	n;

	n = 0;
	map_pars->first = NULL;
	map_pars->hudrep = 0;
	while (get_next_line(fd, &map_pars->line))
	{
		n = skip_wspace(map_pars->line);
		recup(map_pars->line, map_pars->pars);
		if (map_pars->line[n] == '0')
			ft_rerror(map_pars, NULL, map_pars->line, "ERROR MAP");
		if (map_pars->line[n] == '5')
			map_pars->hud = recuphud(fd, map_pars->line, map_pars);
		else if (map_pars->line[n] == '1')
			map_pars->first = recupmap(fd, map_pars->line, map_pars);
		else
			free(map_pars->line);
	}
	free(map_pars->line);
}

t_parse	*cub_skip_header(int fd)
{
	t_cub_skip	map_pars;

	init_map_pars(&map_pars);
	if (!(map_pars.pars = malloc(sizeof(t_parse))))
		ft_error("ERROR MALLOC", NULL);
	init_pars(map_pars.pars);
	get_map(fd, &map_pars);
	if (map_pars.first == NULL)
		ft_error("NO MAP", map_pars.pars);
	if (map_pars.pars->f == -2 || map_pars.pars->c == -2)
		ft_rerror(&map_pars, NULL, NULL, "ERROR COLOR");
	map_pars.pars->tabhud = ft_lstdtab(map_pars.hud);
	map_pars.pars->tab = ft_lstdtab(map_pars.first);
	create_charcub(map_pars.pars, \
	tab_width(map_pars.pars->tab), map_pars.pars->tab);
	create_charcub(map_pars.pars, \
	tab_width(map_pars.pars->tabhud), map_pars.pars->tabhud);
	if (checkmap(map_pars.pars, &map_pars.lst) == 0)
		ft_error("ERROR CHECKMAP", map_pars.pars);
	get_sprites(&map_pars);
	map_pars.pars->width = tab_width(map_pars.pars->tab);
	map_pars.pars->height = tab_height(map_pars.pars->tab);
	map_pars.pars->hwidth = tab_width(map_pars.pars->tabhud);
	map_pars.pars->hheight = tab_height(map_pars.pars->tabhud);
	return (map_pars.pars);
}
