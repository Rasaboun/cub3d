/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:02:43 by rasaboun          #+#    #+#             */
/*   Updated: 2019/12/03 11:36:47 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	static	t_getnl	b[256];
	char			*tmp;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || read(fd, b[fd].s, 0) == -1)
		return (-1);
	inite_base(&b[fd], line);
	if (b[fd].i == 0 && (b[fd].tmp = gread(fd, &b[fd], line)) <= 0)
		return (b[fd].tmp);
	while (1)
	{
		if ((b[Z].tmp = gwasread(b[Z].s + b[Z].i, b[Z].l - b[Z].i)) < 0)
			*line = join(*line, b[Z].s + b[Z].i, &b[Z].ll, b[Z].l - b[Z].i);
		else
		{
			tmp = ft_subbstr(b[fd].s + b[fd].i, 0, b[fd].tmp);
			*line = join(*line, tmp, &b[fd].ll, b[fd].tmp);
			free(tmp);
		}
		b[fd].i = ((b[fd].tmp < 0) ? 0 : b[fd].i + b[fd].tmp + 1);
		if (b[fd].tmp >= 0)
			break ;
		if ((b[fd].tmp = gread(fd, &b[fd], line)) <= 0)
			return (b[fd].tmp);
	}
	return (1);
}
