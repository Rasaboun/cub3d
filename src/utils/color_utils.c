/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 23:22:15 by user42            #+#    #+#             */
/*   Updated: 2023/03/14 14:02:35 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include "../libft/libft.h"
#include "../include/get_next_line.h"
#include "../include/raycast.h"

int		parse_color(char *line, int n, t_rgbcolor *rgb)
{
	while (ft_iswhitespace(line[n]))
		n++;
	rgb->r = ft_atoi(line + n);
	while (ft_isdigit(line[n]))
		n++;
	while (ft_iswhitespace(line[n]))
		n++;
	if (ft_isdigit(line[n]) == 1)
		return (-1);
	if (line[n] != ',')
		return (-1);
	n += 1;
	while (ft_iswhitespace(line[n]))
		n++;
	if (ft_isdigit(line[n]) != 1)
		return (-1);
	rgb->g = ft_atoi(line + n);
	while (ft_isdigit(line[n]))
		n++;
	return (n);
}

int		parsecolor(char *line, int n)
{
	t_rgbcolor rgb;

	rgb.r = 0;
	rgb.g = 0;
	rgb.b = 0;
	rgb.rgb = 0;
	if ((n = parse_color(line, n, &rgb)) <= 0)
		return (-1);
	while (ft_iswhitespace(line[n]))
		n++;
	if (ft_isdigit(line[n]) == 1)
		return (-1);
	if (line[n] != ',')
		return (-1);
	n += 1;
	while (ft_iswhitespace(line[n]))
		n++;
	if (ft_isdigit(line[n]) != 1)
		return (-1);
	rgb.b = ft_atoi(line + n);
	if (rgb.r > 255 || rgb.g > 255 || \
	rgb.b > 255 || rgb.r < 0 || rgb.g < 0 || rgb.b < 0)
		return (-1);
	rgb.rgb = rgb.r << 16 | rgb.g << 8 | rgb.b;
	return (rgb.rgb);
}
