/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 22:57:01 by rasaboun          #+#    #+#             */
/*   Updated: 2020/12/16 00:34:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "libft/libft.h"
#include "get_next_line.h"

int	parsecolor(char *line, int n)
{
	int r;
	int g;
	int b;
	int rgb;

	r = 0;
	g = 0;
	b = 0;
	rgb = 0;
	while (ft_iswhitespace(line[n]))
		n++;
	r = ft_atoi(line + n);
	while (ft_isdigit(line[n]))
		n++;
	while (ft_iswhitespace(line[n]))
		n++;
	if (ft_isdigit(line[n]) == 1)
		return(-1);
	if (line[n] != ',')
		return(-1);
	n += 1;
	while (ft_iswhitespace(line[n]))
		n++;
	if (ft_isdigit(line[n]) != 1)
		return(-1);
	g = ft_atoi(line + n);
	while (ft_isdigit(line[n]))
		n++;
	while (ft_iswhitespace(line[n]))
		n++;
	if (ft_isdigit(line[n]) == 1)
		return(-1);
	if (line[n] != ',')
		return(-1);
	n += 1;
	while (ft_iswhitespace(line[n]))
		n++;
	if (ft_isdigit(line[n]) != 1)
		return(-1);
	b = ft_atoi(line + n);
	if(r > 255 || g > 255 || b > 255)
		return(-1);
	rgb = r << 16 | g << 8 | b;
	return (rgb);
}

doubleint	parsesize(char *line, int n)
{
	doubleint dint;

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

char	*parsetex(char *line, int n)
{
	int		y;
	int		nn;
	char	*s1;

	y = 0;
	nn = 0;
	s1 = NULL;
	while (ft_iswhitespace(line[n]) && line[n])
		n++;
	if (n == ft_strlen(line))
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
/*
void	ft_dupppar(parse *pars,char *line, int n)
{
	if (line[n] == 'S' && line[n + 1] != 'O')
		if (pars->s != NULL)
			ft_error("Error Param",pars);
	if (line[n] == 'R')
		if (pars->r.alr == 1)
			ft_error("Error Param",pars);
	if (line[n] == 'N' && line[n + 1] == 'O')
		if (pars->no != NULL)
			ft_error("Error Param",pars);
	if (line[n] == 'S' && line[n + 1] == 'O')
		if (pars->so != NULL)
			ft_error("Error Param",pars);
	if (line[n] == 'W' && line[n + 1] == 'E')
		if (pars->we != NULL)
			ft_error("Error Param",pars);
	if (line[n] == 'E' && line[n + 1] == 'A')
		if (pars->ea != NULL)
			ft_error("Error Param",pars);
	if (line[n] == 'F')
		if (pars->f != NULL)
			ft_error("Error Param",pars);
	if (line[n] == 'C')
		if (pars->c != NULL)
			ft_error("Error Param",pars);
}
*/
void	recuptwo(char *line, parse *pars)
{
	int n;

	n = 0;

	if (line[n] == 'S' && line[n + 1] != 'O')
	{
		n++;
		pars->s = parsetex(line, n);
	}
	if (line[n] == 'R')
	{
		n++;
		pars->r = parsesize(line, n);
	}
	if (line[n] == 'N' && line[n + 1] == 'O')
	{
		n += 2;
		pars->no = parsetex(line, n);
	}
	if (line[n] == 'S' && line[n + 1] == 'O')
	{
		n += 2;
		pars->so = parsetex(line, n);
	}
	if (line[n] == 'W' && line[n + 1] == 'E')
	{
		n += 2;
		pars->we = parsetex(line, n);
	}
}

void	recup(char *line, parse *pars)
{
	int n;
	static int alrd;
	alrd = 0;
	n = 0;
	recuptwo(line, pars);
	if (line[n] == 'E' && line[n + 1] == 'A')
	{
		alrd += 1;
		n += 2;
		pars->ea = parsetex(line, n);
	}
	if (line[n] == 'F')
	{
		n++;
		pars->f = parsecolor(line, n);
	}
	if (line[n] == 'C')
	{
		n++;
		pars->c = parsecolor(line, n);
	}
	if(alrd >= 2)
		ft_error("error param",pars);
}
