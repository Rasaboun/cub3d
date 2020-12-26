/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 21:44:07 by user42            #+#    #+#             */
/*   Updated: 2020/12/26 19:14:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test.h"
#include "../libft/libft.h"
#include "../get_next_line.h"
#include "../raycast.h"

void	ft_swap_sprite(t_sprite **one, int j)
{
	t_sprite *tmp;

	tmp = one[j + 1];
	one[j + 1] = one[j];
	one[j] = tmp;
}

int		ft_calcul_dist(int x, int y, int posx, int posy)
{
	return (pow((posx - x), 2) + pow((posy - y), 2));
}

void	sort_sprite(t_sprite **spr, int posx, int posy, int size)
{
	int disorder;
	int dist1;
	int dist2;
	int j;

	j = 0;
	dist1 = 0;
	dist2 = 0;
	disorder = 1;
	while (spr != NULL && disorder)
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
