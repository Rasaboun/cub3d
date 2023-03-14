/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:05:52 by rasaboun          #+#    #+#             */
/*   Updated: 2019/12/03 11:13:54 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			gread(int fd, t_getnl *base, char **line)
{
	base->l = read(fd, base->s, BUFFER_SIZE);
	if (base->l > 0)
		base->s[base->l] = '\0';
	if (base->l == 0)
		return (0);
	if (base->l == -1)
	{
		free(*line);
		return (-1);
	}
	return (1);
}

int			gwasread(char *s, int len)
{
	int	i;

	if (!s)
		return (-2);
	i = 0;
	while (i < len)
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char		*join(char *s1, char *s2, int *s_s1, int s_s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	if (!(str = malloc((*s_s1 + s_s2 + 1) * sizeof(char))))
		return (NULL);
	i = -1;
	while (++i < *s_s1)
		str[i] = s1[i];
	j = i;
	i = -1;
	while (++i < s_s2)
		str[j + i] = s2[i];
	*s_s1 += s_s2;
	str[j + i] = '\0';
	free(s1);
	return (str);
}

char		*ft_subbstr(char *s, int start, int len)
{
	char	*str;
	int		i;

	if (!s)
		return (NULL);
	if (!(str = (char*)malloc((len + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void		inite_base(t_getnl *base, char **line)
{
	base->ll = 0;
	*line = malloc(sizeof(char));
	*line[0] = 0;
}
