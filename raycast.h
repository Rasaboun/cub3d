#ifndef RAYCAST_H
#define RAYCAST_H

#include <stdlib.h>
#include <math.h>
#include <mlx.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft/libft.h"
#include "test.h"

#define KEY_PRESSED 2
#define KEY_RELEASE 3
#define CLOSE_EVENT 17

typedef struct texture
{
    int textwidth;
    int textheight;
    char *path;
    void *img;
    int bpp;
    int size_line;
    int endian;
    int *imagedata;
    void *mlx;
} texture;

typedef struct mini
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
} mini;

typedef struct ddas
{

    double perpWallDist;
    int mapy;
    int mapx;
    double sidedistx;
    double sidedisty;
    double raydiry;
    double raydirx;
    int side;
    double camerax;
	double deltadistx;
	double deltadisty;
	int stepx;
	int stepy;
	int hit;
} ddas;

typedef struct draws
{

    double spritex;
    double spritey;
    double invdet;
    double transformx;
    double transformy;
    int spritescreenx;
    int spriteheight;
    int drawstarty;
    int drawendy;
    int spritewidth;
    int drawstartx;
    int drawendx;
    int stripe;
    int texx;
    int d;
    int texy;
    int yy;
    int colors;
    int texnum;
    double wallx;
    int charint;
    double texpos;
    double step;
    int lineheight;
    int drawstart;
    int drawend;
} draws;

typedef struct raycasting
{
    void *mlx;
    void *mlx_win;
    double posx;
    double posy;
    double dirx;
    double diry;
    double planex;
    double planey;
    int w;
    int h;
    int screenx;
    int screeny;
    unsigned int *imagescreenb;
    int size_line;
    void *screenb;
    texture *textures;
    parse *pars;
    int save;
    double perpwalldist;
    int mapx;
    int mapy;
    double raydirx;
    double raydiry;
    int side;
    int forward;
    int back;
    int left;
    int right;
    int rotate_left;
    int rotate_right;
} raycasting;

int deal_key(int key, void *param);
int raycast(raycasting *ray);
void ft_draw(raycasting *ray, int x, double *zbuffer);
void	ft_drawthree(draws *draw, raycasting *ray, int x);
void	ft_drawtwo(draws *draw, raycasting *ray);
void ft_dda(raycasting *ray, int x);
void	initdda(ddas *dd, raycasting *ray, int x);
void	findhit(raycasting *ray, ddas *dd);
void	choosedir(raycasting *ray, ddas *dd);
void freeall(parse *pars);
void ft_draw_sprites(raycasting *ray, int y, double *zbuffer);
void ft_initdraws(draws *ds, raycasting *ray, int y);
void ft_startinitdraws(draws *ds);
int ft_key_press(int key, void *param);
void	ft_drawspritetwo(draws *ds, raycasting *ray, double *zbuffer);
int ft_key_release(int key, void *param);
void move_forward(raycasting *ray);
void move_back(raycasting *ray);
void move_right(raycasting *ray);
void move_left(raycasting *ray);
void turn_left(raycasting *ray);
void turn_right(raycasting *ray);
void freeall(parse *pars);
int raycast(raycasting *ray);
void freecubskip(cub_skip *map_pars);
int *mlx_data_xpm(char *path, int fd, int *data);
void xpm_skip_header(int fd);
void get_data_xpm(int fd, int *data);
int xpmidcolor(int fd, int *data, xpmcolordata *idcolor);
char *xpmimgdata(int fd, int *data);
int convert(char *s, xpmcolordata *idcolor, int *data, int i);
int *xpmtoint(char *imgs, int *data, xpmcolordata *idcolor);
int ft_iswhitespace(char const c);
int ft_atoi_base(const char *str, int str_base);
int base(int c, int base);
void ft_error(char *str, parse *pars);
int save_bitmap(unsigned int *color, int width, int height, int fd);
t_list	*recupmap(int fd, char *line, cub_skip *map_pars);
t_list	*recuphud(int fd, char *line, cub_skip *map_pars);
int	parse_color(char *line, int n, rgbcolor *rgb);
int	parsecolor(char *line, int n);
void	ft_rrerror(cub_skip *map_pars, t_list *first);
#endif
