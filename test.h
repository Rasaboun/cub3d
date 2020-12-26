/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 00:32:02 by user42            #+#    #+#             */
/*   Updated: 2020/12/26 14:24:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H

# define TEST_H

# include <stdlib.h>
# include <math.h>
# include "./minilibx-linux/mlx.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "libft/libft.h"

typedef	struct	s_bfh
{
	unsigned	char	bitmap[2];
	int					file_size;
	short				reserved1;
	short				reserverd2;
	unsigned	int		offset_bits;
}				t_bfh;

typedef	struct	s_bih
{
	unsigned		size_header;
	unsigned	int	width;
	unsigned	int	height;
	short	int		planes;
	short	int		bit_count;
	unsigned	int	compression;
	unsigned	int	image_size;
	unsigned	int	ppm_x;
	unsigned	int	ppm_y;
	unsigned	int	clr_used;
	unsigned	int	clr_important;
}				t_bih;

typedef struct	s_doubleint
{
	int	i;
	int	ii;
	int	alr;
}				t_doubleint;

typedef struct	s_sprite
{
	int x;
	int y;
}				t_sprite;

typedef struct	s_player
{
	int		x;
	int		y;
	char	direction;
}				t_player;

typedef struct	s_rgbcolor
{
	int r;
	int g;
	int b;
	int rgb;
}				t_rgbcolor;

typedef	struct	s_parse
{
	char		*s;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	t_doubleint	r;
	int			f;
	int			c;
	char		**tab;
	int			row;
	t_sprite	**sprites;
	t_player	play;
	int			width;
	int			height;
	int			hwidth;
	int			hheight;
	char		**tabhud;
}				t_parse;

typedef	struct	s_textures
{
	char	*line;
	int		data[4];
	int		fd;
	char	*s;
	char	*path;
	int		*imagedata;

}				t_textures;

typedef struct	s_data
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
	int		*resolution;
	int		c;
	int		f;
}				t_data;

typedef struct	s_mlxf
{
	char	*path;
	int		fd;
	char	*line;
	char	*s;
	int		*data;
}				t_mlxf;

typedef struct	s_cub_skip
{
	char		*line;
	int			n;
	t_list		*first;
	t_parse		*pars;
	t_list		*lst;
	t_sprite	**sprites;
	t_list		*hud;
	int			hudrep;
}				t_cub_skip;

typedef struct	s_checkmap
{
	int			linecount;
	int			i;
	int			j;
	char		mapf;
	int			player;
	char		*play;
	t_sprite	*sprites;
	t_list		*new;
}				t_checkmap;

void			freecubskip(t_cub_skip *map_pars);
int				*mlx_data_xpm(char *path, int fd, int *data);
void			xpm_skip_header(int fd);
void			get_data_xpm(int fd, int *data);
char			*xpmimgdata(int fd, int *data);
int				ft_iswhitespace(char const c);
int				ft_atoi_base(const char *str, int str_base);
int				base(int c, int base);
void			ft_error(char *str, t_parse *pars);
int				save_bitmap(unsigned int *color, int width, int height, int fd);
int				save_bmp(int width, unsigned int *color, int i, int fd);
void			recup(char *line, t_parse *pars);
char			*parsetex(char *line, int n);
t_doubleint		parsesize(char *line, int n);
int				parsecolor(char *line, int n);
void			sort_sprite(t_sprite **sprites, int posx, int posy, int size);
void			get_sprites(t_cub_skip *map_pars);
int				close_map(t_parse *pars, int i, int j);
int				checkmap(t_parse *pars, t_list **lst);
char			**ft_lstdtab(t_list *lst);
t_list			*recupmap(int fd, char *line, t_cub_skip *map_pars);
void			init_pars(t_parse *pars);
t_parse			*cub_skip_header(int fd);
int				tab_width(char **tab);
void			create_charcub(t_parse *pars, int width, char **tab);
void			get_map(int fd, t_cub_skip *map_pars);
void			ft_swap_sprite(t_sprite **one, int j);
int				ft_while(char *s3, const char *s1, int i);
char			*ft_strjoinzero(char *s1, int size, t_parse *pars);
void			ft_swap_sprite(t_sprite **one, int j);
int				ft_calcul_dist(int x, int y, int posx, int posy);
void			get_sprites(t_cub_skip *map_pars);
void			freesprite(t_parse *pars);
int				ft_getelemmap(t_parse *pars, t_checkmap *ck, t_list **lst);
void			ft_getspritemap(t_checkmap *ck, t_list **lst);
void			ft_getplayermap(t_parse *pars, t_checkmap *ck);
void			freepars(t_parse *pars);
int				tab_height(char **tab);
void			duplicerror(char *s, t_parse *pars);
t_list			*recupmap(int fd, char *line, t_cub_skip *map_pars);
t_list			*recuphud(int fd, char *line, t_cub_skip *map_pars);
int				skip_wspace(char *s);
void			ft_rerror(t_cub_skip *map_pars,
				t_list *first, char *line, char *str);
void			freemap(t_parse *pars);
void			freehud(t_parse *pars);
void			freesprite(t_parse *pars);
void			freetext(t_parse *pars);
void			init_map_pars(t_cub_skip *map_pars);
void			file_headers(unsigned char *file_header, int file_size,
				int width, unsigned char *image_header);
int				save_bmp(int width, unsigned int *color, int i, int fd);
void			ft_errord(char *str, t_parse *pars, char *line);
#endif
