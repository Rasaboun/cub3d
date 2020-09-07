/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:56:39 by rasaboun          #+#    #+#             */
/*   Updated: 2019/12/03 11:15:31 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define Z fd
# define BUFFER_SIZE 256
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct	s_getnl
{
	int		fd;
	int		i;
	char	s[BUFFER_SIZE + 1];
	int		l;
	int		ll;
	int		tmp;
}				t_getnl;

int				gwasread(char *str, int i);
int				gread(int fd, t_getnl *base, char **line);
char			*join(char *s1, char *s2, int *s_s1, int s_s2);
char			*ft_subbstr(char *s, int start, int len);
void			inite_base(t_getnl *base, char **line);
int				get_next_line(int fd, char **line);
#endif
