#ifndef RAYCAST_H
#define RAYCAST_H

#include <stdlib.h>
#include <math.h>
#include <mlx.h>
#include <unistd.h>
#include "test.h"

#define screenWidth 1200
#define screenHeight 720
#define KEY_PRESSED 2
#define KEY_RELEASE 3
#define CLOSE_EVENT 17
#define PATH "/home/user42/Bureau/cub3d/open.xpm","/home/user42/Bureau/cub3d/open.xpm","/home/user42/Bureau/cub3d/open.xpm","/home/user42/Bureau/cub3d/open.xpm"


typedef struct texture
{
    int             textwidth;
    int             textheight;
    char            *path;
    void            *img;
    int             bpp;
    int             size_line;
    int             endian;
    int    *imagedata;
    	void *mlx;


} texture;

typedef struct dda
{

    double perpWallDist;
    int mapy;
    int mapx;
	double sidedistx;
	double sidedisty;
    double raydiry;
    double raydirx;
    int side;
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
} draws;

typedef struct raycasting
{
    void    *mlx;
    void    *mlx_win;
    double  posx;
    double  posy;
    double  dirx;
    double  diry;
    double  planex;
    double  planey;
    int     w;
    int     h;
    int     screenx;
    int     screeny;
    unsigned int     *imagescreenb;
    int size_line;
    void* screenB;
    texture         *texture;
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
void    ft_draw(raycasting *ray, int x,double *zbuffer);
void    ft_dda(raycasting *ray, int x);
void freeall(parse *pars);
void ft_draw_sprites(raycasting *ray, int y,double *zbuffer);
int ft_key_press(int key, void *param);
int ft_key_release(int key, void *param);
 void    move_forward(raycasting *ray);
  void    move_back(raycasting *ray);
   void    move_right(raycasting *ray);
 void    move_left(raycasting *ray);
 void    turn_left(raycasting *ray);
  void    turn_right(raycasting *ray);
#endif
