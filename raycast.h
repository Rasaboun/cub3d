#ifndef RAYCAST_H
#define RAYCAST_H

#include <stdlib.h>
#include <math.h>
#include <mlx.h>
#include <unistd.h>
#include "test.h"

#define screenWidth 1680
#define screenHeight 1050
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

} texture;

typedef struct raycasting
{
    void    *mlx;
    void    *mlx_win;
    double  posX;
    double  posY;
    double  dirX;
    double  dirY;
    double  planeX;
    double  planeY;
    int     w;
    int     h;
    unsigned int     *imagescreenB;
    int size_line;
    void* screenB;
    texture         *texture;
    parse *pars;
} raycasting;


int deal_key(int key, void *param);
int raycast(raycasting *ray);

#endif
