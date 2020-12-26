/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 23:05:03 by rasaboun          #+#    #+#             */
/*   Updated: 2020/12/23 23:01:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	ft_error(char *str, t_parse *pars)
{
	if (pars != NULL)
		freeall(pars);
	ft_putstr_fd(str, 1);
	exit(EXIT_FAILURE);
}

void	ft_errord(char *str, t_parse *pars, char *line)
{
	if (pars != NULL)
		freeall(pars);
	if (line != NULL)
		free(line);
	ft_putstr_fd(str, 1);
	exit(EXIT_FAILURE);
}
