/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 23:03:30 by rasaboun          #+#    #+#             */
/*   Updated: 2023/03/13 15:25:49 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

int		save_bmp(int width, unsigned int *color, int i, int fd)
{
	int colors;
	int j;

	j = 0;
	colors = 0;
	while (i >= 0)
	{
		j = 0;
		while (j < width)
		{
			colors = color[i * width + j];
			if (write(fd, &colors, 3) == 0)
				return (0);
			j++;
		}
		i--;
	}
	return (1);
}

void	file_headers(unsigned char *file_header, int file_size, \
int width, unsigned char *image_header)
{
	file_header[2] = (unsigned char)file_size;
	file_header[3] = (unsigned char)(file_size >> 8);
	file_header[4] = (unsigned char)(file_size >> 16);
	file_header[5] = (unsigned char)(file_size >> 24);
	file_header[10] = (unsigned char)(14 + 40);
	image_header[0] = (unsigned char)40;
	image_header[4] = (unsigned char)width;
	image_header[5] = (unsigned char)(width >> 8);
	image_header[6] = (unsigned char)(width >> 16);
	image_header[7] = (unsigned char)(width >> 24);
	image_header[12] = (unsigned char)1;
	image_header[14] = (unsigned char)24;
}

int		save_bitmap(unsigned int *color, int width, int height, int fd)
{
	unsigned	char	file_header[14];
	unsigned	char	image_header[40];
	int					file_size;
	int					i;

	i = (height - 1);
	file_size = 14 + 40 + (3 * width * height);
	ft_bzero(file_header, 14);
	ft_bzero(image_header, 40);
	file_header[0] = 'B';
	file_header[1] = 'M';
	file_headers(file_header, file_size, width, image_header);
	image_header[8] = (unsigned char)height;
	image_header[9] = (unsigned char)(height >> 8);
	image_header[10] = (unsigned char)(height >> 16);
	image_header[11] = (unsigned char)(height >> 24);
	if (write(fd, &file_header, 14) == 0)
		return (0);
	if (write(fd, &image_header, 40) == 0)
		return (0);
	if (save_bmp(width, color, i, fd) == 0)
		return (0);
	return (1);
}
