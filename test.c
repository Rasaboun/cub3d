/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 23:05:03 by rasaboun          #+#    #+#             */
/*   Updated: 2020/11/14 00:32:44 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	ft_iswhitespace(char const c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || \
	c == '\r' || c == '\f')
		return (1);
	return (0);
}

int	base(int c, int base)
{
	char	*str;
	char	*str2;
	int		i;

	i = 0;
	str2 = "0123456789ABCDEF";
	str = "0123456789abcdef";
	while (i < base)
	{
		if (c == str[i] || c == str2[i])
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int nb;
	int negatif;
	int i;

	nb = 0;
	negatif = 0;
	i = 0;
	while (ft_iswhitespace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			negatif = 1;
		i++;
	}
	while (base(str[i], str_base) != -1)
	{
		nb = nb * str_base;
		nb = nb + base(str[i], str_base);
		i++;
	}
	if (negatif)
		return (-nb);
	return (nb);
}

int		*mlx_data_xpm(char *path, int fd, int *data)
{
	xpmcolordata	*idcolor;
	char			*imgdata;
	int				*im;
	int				i;

	i = 0;
	imgdata = NULL;
	xpm_skip_header(fd);
	get_data_xpm(fd, data);
	if (data[2] != 0)
		idcolor = malloc((sizeof(xpmcolordata) * data[2]));
	xpmidcolor(fd, data, idcolor);
	imgdata = xpmimgdata(fd, data);
	im = xpmtoint(imgdata, data, idcolor);
	while (i < data[2])
	{
		free(idcolor[i].id);
		i++;
	}
	free(idcolor);
	return (im);
}

void	xpm_skip_header(int fd)
{
	char *line;

	line = NULL;
	while (get_next_line(fd, &line) && ft_strcmp(line, XPMCOMMENT) != 0)
	{
		free(line);
	}
	if (line != NULL)
		free(line);
	else
		ft_error("ERROR TEXTURE FILE");
}

void	get_data_xpm(int fd, int *data)
{
	int		i;
	int		j;
	int		n;
	char	*tmp;
	char	*line;

	line = NULL;
	tmp = NULL;
	j = 0;
	i = 0;
	n = 0;
	if (get_next_line(fd, &line))
	{
		while (line[i] != 0 && n < 4)
		{
			while ((line[i] < '0' || line[i] > '9') && line[i] != 0)
				i++;
			while ((line[i + j] >= '0' && line[i + j] <= '9') && \
				line[i + j] != 0)
				j++;
			tmp = ft_substr(line, i, j);
			i = i + j;
			j = 0;
			data[n] = ft_atoi(tmp);
			free(tmp);
			n++;
		}
	}
	else
		ft_error("ERROR TEXTURE FILE");
	free(line);
}

int		xpmidcolor(int fd, int *data, xpmcolordata *idcolor)
{
	int		i;
	int		n;
	char	*line;

	line = NULL;
	n = data[3];
	i = 0;
	while (i < data[2])
	{
		if (get_next_line(fd, &line) <= 0)
		{
			ft_error("ERROR TEXTURE FILE");
			return (0);
		}
		idcolor[i].id = ft_substr(line, 1, data[3]);
		while (ft_iswhitespace(line[n]) || line[n] == 'c' || line[n] == '#')
			n++;
		if (ft_strncmp(line + n, "None", 4) == 0 || \
		ft_strncmp(line + n, "none", 4) == 0)
			idcolor[i].color = -1;
		else
		{
			idcolor[i].color = ft_atoi_base(line + n, 16);
		}
		i++;
		free(line);
	}
	return (1);
}

char	*xpmimgdata(int fd, int *data)
{
	char	*imgdata;
	int		i;
	char	*tmp;
	char	*line;

	line = 0;
	imgdata = ft_calloc(1, sizeof(int));
	i = 0;
	while (i < data[1])
	{
		if (get_next_line(fd, &line) <= 0)
		{
			ft_error("ERROR TEXTURE FILE");
			return (NULL);
		}
		if (line[0] == '/')
		{
			free(line);
			if (get_next_line(fd, &line) <= 0)
			{
				ft_error("ERROR TEXTURE FILE");
				return (NULL);
			}
		}
		if (line == NULL || line[0] == ' ')
			ft_error("ERROR TEXTURE FILE");
		tmp = ft_substr(line, 1, data[0] * data[3]);
		imgdata = ft_strfjoin(imgdata, tmp);
		free(line);
		i++;
	}
	return (imgdata);
}

int		*xpmtoint(char *imgs, int *data, xpmcolordata *idcolor)
{
	int		*imgdataint;
	int		i;
	char	*tmp;
	int		y;

	y = 0;
	tmp = NULL;
	imgdataint = NULL;
	i = 0;
	if (!(imgdataint = malloc(sizeof(int) * (data[0] * data[1]) + 1)))
		ft_error("FAIL MALLOC");
	while (i < (data[0] * data[3]) * data[1])
	{
		imgdataint[y] = convert(imgs, idcolor, data, i);
		i = i + data[3];
		y++;
	}
	free(imgs);
	return (imgdataint);
}

int		convert(char *s, xpmcolordata *idcolor, int *data, int i)
{
	int y;

	y = 0;
	while (ft_strncmp(s + i, idcolor[y].id, data[3]) && y < data[2])
	{
		y++;
	}
	return (idcolor[y].color);
}

void	ft_error(char *str)
{
	ft_putstr_fd(str, 1);
	exit(EXIT_FAILURE);
}
