/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 23:05:03 by rasaboun          #+#    #+#             */
/*   Updated: 2020/12/15 23:09:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "raycast.h"

void	ft_error(char *str,parse *pars)
{
	freeall(pars);
	ft_putstr_fd(str, 1);
	exit(EXIT_FAILURE);
}
