/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 22:57:01 by rasaboun          #+#    #+#             */
/*   Updated: 2020/12/23 23:00:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "libft/libft.h"
#include "get_next_line.h"

t_doubleint	parsesize(char *line, int n)
{
	t_doubleint dint;

	dint.i = 0;
	dint.ii = 0;
	while (ft_iswhitespace(line[n]))
		n++;
	dint.i = ft_atoi(line + n);
	while (ft_isdigit(line[n]))
		n++;
	while (ft_iswhitespace(line[n]))
		n++;
	dint.ii = ft_atoi(line + n);
	dint.alr = 1;
	return (dint);
}

char		*parsetex(char *line, int n)
{
	int		y;
	int		nn;
	char	*s1;

	y = 0;
	nn = 0;
	s1 = NULL;
	while (ft_iswhitespace(line[n]) && line[n])
		n++;
	if (n == (int)ft_strlen(line))
		return (NULL);
	nn = n;
	while (line[n] >= 33 && line[n] <= 126)
	{
		y++;
		n++;
	}
	s1 = ft_substr(line, nn, y);
	return (s1);
}

void		recupthree(char *line, t_parse *pars)
{
	int n;

	n = skip_wspace(line);
	if (line[n] == 'S' && line[n + 1] != 'O')
	{
		if (pars->s != NULL)
			ft_errord("duplicate arg", pars, line);
		n++;
		pars->s = parsetex(line, n);
	}
	if (line[n] == 'R')
	{
		if (pars->r.alr == 1)
			ft_error("duplicate", pars);
		n++;
		pars->r = parsesize(line, n);
	}
	if (line[n] == 'N' && line[n + 1] == 'O')
	{
		if (pars->no != NULL)
			ft_errord("duplicate arg", pars, line);
		n += 2;
		pars->no = parsetex(line, n);
	}
}

void		recuptwo(char *line, t_parse *pars)
{
	int n;

	n = skip_wspace(line);
	recupthree(line, pars);
	if (line[n] == 'S' && line[n + 1] == 'O')
	{
		if (pars->so != NULL)
			ft_errord("duplicate arg", pars, line);
		n += 2;
		pars->so = parsetex(line, n);
	}
	if (line[n] == 'W' && line[n + 1] == 'E')
	{
		if (pars->we != NULL)
			ft_errord("duplicate arg", pars, line);
		n += 2;
		pars->we = parsetex(line, n);
	}
}

void		recup(char *line, t_parse *pars)
{
	int n;

	n = skip_wspace(line);
	recuptwo(line, pars);
	if (line[n] == 'E' && line[n + 1] == 'A')
	{
		if (pars->ea != NULL)
			ft_errord("duplicate arg", pars, line);
		n += 2;
		pars->ea = parsetex(line, n);
	}
	if (line[n] == 'F')
	{
		if (pars->f != -2)
			ft_error("duplicate", pars);
		n++;
		pars->f = parsecolor(line, n);
	}
	if (line[n] == 'C')
	{
		if (pars->c != -2)
			ft_error("duplicate", pars);
		n++;
		pars->c = parsecolor(line, n);
	}
}
