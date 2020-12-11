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
    unsigned int     *imagescreenB;
    int size_line;
    void* screenB;
    texture         *texture;
    parse *pars;
    int save;
} raycasting;


int deal_key(int key, void *param);
int raycast(raycasting *ray);

#endif
