/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 00:21:47 by user42            #+#    #+#             */
/*   Updated: 2020/12/26 14:24:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include <stdlib.h>
# include <math.h>
# include "./minilibx-linux/mlx.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "libft/libft.h"
# include "test.h"

# define KEY_PRESSED 2
# define KEY_RELEASE 3
# define CLOSE_EVENT 17

typedef	struct	s_texture
{
	int		textwidth;
	int		textheight;
	char	*path;
	void	*img;
	int		bpp;
	int		size_line;
	int		endian;
	int		*imagedata;
	void	*mlx;
}				t_texture;

typedef	struct	s_mini
{
	int width;
	int height;
	int margel;
	int marget;
	int i;
	int y;
	int color;
	int size_x;
	int size_y;
	int ratio_x;
	int ratio_y;
	int ii;
	int yy;
	int sp;
}				t_mini;

typedef	struct	s_mains
{
	int				fdd;
	void			*screenb;
	unsigned	int	*imagescreenb;
	void			*mlx;
	int				screenx;
	int				screeny;
	void			*mlx_win;
	int				bpp;
	int				size_line;
	int				endian;
}				t_mains;

typedef	struct	s_ddas
{

	double	perpwalldist;
	int		mapy;
	int		mapx;
	double	sidedistx;
	double	sidedisty;
	double	raydiry;
	double	raydirx;
	int		side;
	double	camerax;
	double	deltadistx;
	double	deltadisty;
	int		stepx;
	int		stepy;
	int		hit;
}				t_ddas;

typedef	struct	s_draws
{

	double	spritex;
	double	spritey;
	double	invdet;
	double	transformx;
	double	transformy;
	int		spritescreenx;
	int		spriteheight;
	int		drawstarty;
	int		drawendy;
	int		spritewidth;
	int		drawstartx;
	int		drawendx;
	int		stripe;
	int		texx;
	int		d;
	int		texy;
	int		yy;
	int		colors;
	int		texnum;
	double	wallx;
	int		charint;
	double	texpos;
	double	step;
	int		lineheight;
	int		drawstart;
	int		drawend;
}				t_draws;

typedef	struct	s_raycasting
{
	void			*mlx;
	void			*mlx_win;
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	int				w;
	int				h;
	int				screenx;
	int				screeny;
	unsigned	int	*imagescreenb;
	int				size_line;
	void			*screenb;
	t_texture		*textures;
	t_parse			*pars;
	int				save;
	double			perpwalldist;
	int				mapx;
	int				mapy;
	double			raydirx;
	double			raydiry;
	int				side;
	int				forward;
	int				back;
	int				left;
	int				right;
	int				rotate_left;
	int				rotate_right;
}				t_raycasting;

int				raycast(t_raycasting *ray);
void			ft_draw(t_raycasting *ray, int x, double *zbuffer);
void			ft_drawthree(t_draws *draw, t_raycasting *ray, int x);
void			ft_drawtwo(t_draws *draw, t_raycasting *ray);
void			ft_dda(t_raycasting *ray, int x);
void			initdda(t_ddas *dd, t_raycasting *ray, int x);
void			findhit(t_raycasting *ray, t_ddas *dd);
void			choosedir(t_raycasting *ray, t_ddas *dd);
void			freeall(t_parse *pars);
void			ft_draw_sprites(t_raycasting *ray, int y, double *zbuffer);
int				ft_initdraws(t_draws *ds, t_raycasting *ray, int y);
void			ft_startinitdraws(t_draws *ds);
int				ft_key_press(int key, void *param);
int				escape(void *param);
void			ft_drawspritetwo(t_draws *ds,
				t_raycasting *ray, double *zbuffer);
int				ft_key_release(int key, void *param);
void			move_forward(t_raycasting *ray);
void			move_back(t_raycasting *ray);
void			move_right(t_raycasting *ray);
void			move_left(t_raycasting *ray);
void			turn_left(t_raycasting *ray);
void			turn_right(t_raycasting *ray);
void			freeall(t_parse *pars);
int				raycast(t_raycasting *ray);
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
t_list			*recupmap(int fd, char *line, t_cub_skip *map_pars);
t_list			*recuphud(int fd, char *line, t_cub_skip *map_pars);
int				parse_color(char *line, int n, t_rgbcolor *rgb);
int				parsecolor(char *line, int n);
void			ft_rrerror(t_cub_skip *map_pars, t_list *first);
void			put_pixel(t_raycasting *ray, t_mini mn);
void			utils_mmap(t_raycasting *ray, t_mini *ds);
void			mini_map(t_raycasting *ray);
void			mini_life(t_raycasting *ray);
void			chooseplayerdirtwo(t_raycasting *ray, t_parse *pars);
void			chooseplayerdir(t_raycasting *ray, t_parse *pars);
void			argsave(int argc, char **argv,
				t_raycasting *param, t_parse *pars);
void			max_reso(t_parse *pars, t_raycasting *param, int sx, int sy);
t_parse			*check_arg(int argc, char **argv);
void			initcub(t_raycasting *param, t_parse *pars,
				t_texture *textures);
void			ft_checkun(t_parse *pars);
void			init_texture(t_texture *tex, t_parse *pars, void *mlx);
void			intextpath(t_texture *textures, t_parse *pars);
#endif
