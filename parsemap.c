/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsemap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:31:18 by rasaboun          #+#    #+#             */
/*   Updated: 2020/12/11 02:21:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "libft/libft.h"
#include "get_next_line.h"

static	int	ft_while(char *s3, const char *s1, int i)
{
	int p;
	int y;

	p = 0;
	y = 0;
	while (p < i)
	{
		s3[p] = s1[y];
		p++;
		y++;
	}
	return (p);
}

char	*ft_strjoinzero(char *s1, int size)
{
	int p;
	char *s3;
	int y;
	int i;

	if (!s1)
		return (NULL);
	y = 0;
	p = 0;
	i = (int)ft_strlen(s1);
	if (!(s3 = (char *)malloc(sizeof(char) * (i + size + 1))))
		return (0);
	p = ft_while(s3, s1, i);
	y = 0;
	while (p <= (int)(i + size - 1))
	{
		s3[p] = '\0';
		p++;
		y++;
	}
	s3[p] = '\0';
	free(s1);
	return (s3);
}

void	create_charcub(char **tab, int width)
{
	int i;
	int n;
	char *tmp;

	i = 0;
	n = 0;
	if (tab != NULL && width > 0)
		while (tab[n] != NULL)
		{
			i = ft_strlen(tab[n]);
			if (i < width)
				tab[n] = ft_strjoinzero(tab[n], width - i);
			n++;
		}
}

int		tab_width(char **tab)
{
	int i;
	int j;
	int new;
	int last;

	last = 0;
	new = 0;
	i = 0;
	j = 0;
	if (tab != NULL)
		while (tab[i] != NULL)
		{
			j = 0;
			while (tab[i][j])
			{
				j++;
			}
			new = j;
			if (new > last)
				last = new;
			i++;
		}
	return (last);
}

int		tab_height(char **tab)
{
	int i;

	i = 0;
	if (tab != NULL)
		while (tab[i] != NULL)
		{
			i++;
		}
	return (i);
}

static	void	ft_swap_sprite(sprite **one, int j)
{
	sprite *tmp;

	tmp = one[j + 1];
	one[j + 1] = one[j];
	one[j] = tmp;
}

static	int	ft_calcul_dist(int x, int y, int posx, int posy)
{
	return (pow((posx - x), 2) + pow((posy - y), 2));
}

void	sort_sprite(sprite **spr, int posx, int posy, int size)
{
	int disorder;
	int dist1;
	int dist2;
	int j;

	j = 0;
	dist1 = 0;
	dist2 = 0;
	disorder = 1;
	while (disorder)
	{
		disorder = 0;
		j = 0;
		while (j < (size - 1))
		{
			dist1 = ft_calcul_dist(spr[j]->x, spr[j]->y, posx, posy);
			dist2 = ft_calcul_dist(spr[j + 1]->x, spr[j + 1]->y, posx, posy);
			if (dist1 < dist2)
			{
				ft_swap_sprite(spr, j);
				disorder = 1;
			}
			j++;
		}
	}
}

void	get_sprites(cub_skip *map_pars)
{
	int i;
	t_list *tmp;

	i = ft_lstsize(map_pars->lst);
	if (map_pars->lst != NULL)
	{
		map_pars->pars->sprites = (sprite **)malloc(sizeof(sprite *) * (i + 1));
		while(i >= 0)
		{
			map_pars->pars->sprites[i] == NULL;
			i--;
		}
		i = 0;
		while (map_pars->lst != NULL)
		{
			tmp = map_pars->lst->next;
			map_pars->pars->sprites[i] = (sprite *)map_pars->lst->content;
			free(map_pars->lst);
			map_pars->lst = tmp;
			i++;
		}
		map_pars->pars->sprites[i] = NULL;
	}
}

int		close_map(parse *pars, int i, int j)
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

void	freemap(parse *pars)
{
	int i;

	i = 0;
	while (pars->tab[i] != NULL)
	{
		free(pars->tab[i]);
		i++;
	}
	free(pars->tab[i]);
	free(pars->tab);
}

void	freesprite(parse *pars)
{
	int i;

	i = 0;
	while (pars->sprites[i] != NULL)
	{
		free(pars->sprites[i]);
		i++;
	}
	free(pars->sprites[i]);
	free(pars->sprites);
}

void	freetext(parse *pars)
{
	free(pars->ea);
	free(pars->no);
	free(pars->s);
	free(pars->so);
	free(pars->we);
}

void	ft_getplayermap(parse *pars, t_checkmap *ck)
{
	ck->play = ft_strchr("NSWE", ck->mapf);
	pars->play.x = ck->i;
	pars->play.y = ck->j;
	pars->play.direction = ck->mapf;
	ck->player++;
	pars->tab[ck->i][ck->j] = '0';
}

void	ft_getspritemap(parse *pars, t_checkmap *ck, t_list **lst)
{
	ck->sprites = malloc(sizeof(sprite));
	ck->sprites->x = ck->i;
	ck->sprites->y = ck->j;
	ck->new = ft_lstnew(ck->sprites);
	ft_lstadd_back(lst, ck->new);
}

int		ft_getelemmap(parse *pars, t_checkmap *ck, t_list **lst)
{
	ck->mapf = pars->tab[ck->i][ck->j];
	if (!(ft_strchr("012 NSWE", ck->mapf)))
		return (0);
	if (ft_strchr("NSWE", ck->mapf))
		ft_getplayermap(pars, ck);
	if (ft_strchr("2", ck->mapf))
		ft_getspritemap(pars, ck, lst);
	if (ck->mapf == '0' || ck->mapf == '2' || ck->mapf == 'N' ||
		ck->mapf == 'S' || ck->mapf == 'W' || ck->mapf == 'E')
		if (!(close_map(pars, ck->i, ck->j)))
			return (0);		
	return (1);
}

int		checkmap(parse *pars, t_list **lst)
{
	t_checkmap ck;

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
	if(ck.player != 1)
		return(0);
	return (1);
}

char	**ft_lstdtab(t_list *lst)
{
	char	**tab;
	int		i;
	int		size;
	t_list *next;

	t_list *list;

	list = lst;
	i = -1;
	size = ft_lstsize(list);
	next = NULL;
	if (size <= 0)
		return (NULL);
	if (!(tab = (char **)malloc((sizeof(char *) * (size + 1)))))
		exit(0);
	while (i++ < size)
		tab[i] = NULL;
	i = 0;
	while (i < size)
	{
		next = list->next;
		tab[i] = list->content;
		free(list);
		list = next;
		i++;
	}
	free(list);
	tab[size] = NULL;
	return (tab);
}

t_list	*recupmap(int fd, char *line)
{
	t_list *first;
	t_list *map;
	int		n;
	first = NULL;
	map = NULL;
	first = ft_lstnew(line);
	n = 0;
	while (get_next_line(fd, &line) && line)
	{
		n  = 0;
		while(ft_iswhitespace(line[n]))
			n++;
		if(line[n] != '1')
			ft_error("Error Map");
		map = ft_lstnew(line);
		ft_lstadd_back(&first, map);
	}
	map = ft_lstnew(line);
	ft_lstadd_back(&first, map);
	return (first);
}

t_list	*recuphud(int fd, char *line)
{
	t_list *first;
	t_list *map;
	int n;

	n = 0;
	first = NULL;
	map = NULL;
	first = ft_lstnew(line);
	get_next_line(fd, &line);
	while (ft_iswhitespace(line[n]) && line[n] != '\0')
			n++;
	while (line[n] == '5')
	{
		map = ft_lstnew(line);
		ft_lstadd_back(&first, map);
		get_next_line(fd, &line);
		n = 0;
		while (ft_iswhitespace(line[n]) && line[n] != '\0')
			n++;
	}
	return (first);
}

void	freepars(parse *pars)
{
	freetext(pars);
	freemap(pars);
	freesprite(pars);
	free(pars);
}

void	init_pars(parse *pars)
{
	pars->c = 0;
	pars->ea = NULL;
	pars->f = 0;
	pars->no = NULL;
	pars->r.i = 0;
	pars->r.ii = 0;
	pars->s = NULL;
	pars->so = NULL;
	pars->tab = NULL;
	pars->we = NULL;
	pars->sprites = NULL;
}

void	get_map(int fd, cub_skip *map_pars)
{
	int n;

	n = 0;
	map_pars->first = NULL;
	while (get_next_line(fd, &map_pars->line) >= 1)
	{
		if (map_pars->line == NULL)
			exit(0);
		n = 0;
		while (ft_iswhitespace(map_pars->line[n]) == 1 && map_pars->line[n] != '\0')
			n++;
		recup(map_pars->line + n, map_pars->pars);
		if (map_pars->line[n] == '0')
		{
			ft_putstr_fd("ERROR MAP", 1);
			exit(EXIT_FAILURE);
		}
		if (map_pars->line[n] == '5'){
			map_pars->hud = recuphud(fd,map_pars->line);
		}
		else if (map_pars->line[n] == '1')
		{			
			map_pars->first = recupmap(fd, map_pars->line);
		}
		else
			free(map_pars->line);
	}
	free(map_pars->line);
}

parse	*cub_skip_header(int fd)
{
	cub_skip map_pars;
	int n;

	map_pars.lst = NULL;
	n = 0;
	map_pars.line = NULL;
	map_pars.pars = malloc(sizeof(parse));

	init_pars(map_pars.pars);
	get_map(fd, &map_pars);
	if(map_pars.first == NULL)
	{
		ft_error("NO MAP");
	}
	map_pars.pars->tabhud = ft_lstdtab(map_pars.hud);
	map_pars.pars->tab = ft_lstdtab(map_pars.first);

	create_charcub(map_pars.pars->tab, tab_width(map_pars.pars->tab));
	create_charcub(map_pars.pars->tabhud, tab_width(map_pars.pars->tabhud));

	if (checkmap(map_pars.pars, &map_pars.lst) == 0)
	{
		ft_putstr_fd("ERROR MAP", 1);
		exit(0);
	}
	
	get_sprites(&map_pars);

	map_pars.pars->width = tab_width(map_pars.pars->tab);
	map_pars.pars->height = tab_height(map_pars.pars->tab);
	map_pars.pars->hwidth = tab_width(map_pars.pars->tabhud);
	map_pars.pars->hheight = tab_height(map_pars.pars->tabhud);

	return (map_pars.pars);
}
