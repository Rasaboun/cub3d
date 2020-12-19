/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 21:14:25 by user42            #+#    #+#             */
/*   Updated: 2020/12/18 23:48:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test.h"
#include "../libft/libft.h"
#include "../get_next_line.h"
#include "../raycast.h"

int		ft_while(char *s3, const char *s1, int i)
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
	int		p;
	char	*s3;
	int		y;
	int		i;

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
