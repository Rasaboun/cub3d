#include <stdlib.h>
#include <math.h>
#include <mlx.h>
#include <unistd.h>
#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480
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
} raycasting;


int deal_key(int key, void *param);
int raycast(raycasting *ray);