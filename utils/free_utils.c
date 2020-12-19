/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 21:45:35 by user42            #+#    #+#             */
/*   Updated: 2020/12/19 00:13:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test.h"
#include "../libft/libft.h"
#include "../get_next_line.h"
#include "../raycast.h"

void	freemap(parse *pars)
{
	int i;

	i = 0;
	if (pars->tab != NULL)
	{
		while (pars->tab[i] != NULL)
		{
			free(pars->tab[i]);
			i++;
		}
		free(pars->tab[i]);
		free(pars->tab);
	}
}

void	freehud(parse *pars)
{
	int i;

	i = 0;
	if (pars->tabhud != NULL)
	{
		while (pars->tabhud[i] != NULL)
		{
			free(pars->tabhud[i]);
			i++;
		}
		free(pars->tabhud[i]);
		free(pars->tabhud);
	}
}

void	freesprite(parse *pars)
{
	int	i;

	i = 0;
	if (pars->sprites != NULL)
	{
		while (pars->sprites[i] != NULL)
		{
			free(pars->sprites[i]);
			i++;
		}
		free(pars->sprites[i]);
		free(pars->sprites);
	}
}

void	freetext(parse *pars)
{
	if (pars->ea != NULL)
		free(pars->ea);
	if (pars->no != NULL)
		free(pars->no);
	if (pars->s != NULL)
		free(pars->s);
	if (pars->so != NULL)
		free(pars->so);
	if (pars->we != NULL)
		free(pars->we);
}

void	freepars(parse *pars)
{
	freetext(pars);
	freemap(pars);
	freehud(pars);
	freesprite(pars);
	free(pars);
}
