#ifndef TEST_H

#define TEST_H

#include <stdlib.h>
#include <math.h>
#include <mlx.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft/libft.h"


typedef struct bitmap_file_header
{
    unsigned char bitmap[2];;
    int     file_size;
    short reserved1;
    short reserverd2;
    unsigned int offset_bits;
} bfh;

typedef struct bitmap_image_header
{
    unsigned size_header;
    unsigned int width;
    unsigned int height;
    short int planes;
    short int bit_count;
    unsigned int compression;
    unsigned int image_size;
    unsigned int ppm_x;
    unsigned int ppm_y;
    unsigned int clr_used;
    unsigned int clr_important;
} bih;


typedef struct color
{
    char    *id;
    int     color;
} xpmcolordata;

typedef struct doubleint
{
    int    i;
    int    ii;
} doubleint;

typedef struct sprite
{
    int x;
    int y;
}sprite;

typedef struct player
{
    int x;
    int y;
    char direction;
}player;

typedef struct parse
{
    char    *s;
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
    doubleint   r;
    int     f;
    int     c;
    char **tab;
    int row;
    sprite **sprites;
    player play;

} parse;



typedef struct textures
{
    char *line;
    int data[4];
    int fd;
    char *s;
    char            *path;
    int    *imagedata;


} textures;

typedef struct data
{
    char *no;
    char *so;
    char *we;
    char *ea;
    char *s;
    int *resolution;
    int c;
    int f;
} data;


typedef struct mlxf
{
    char *path;
    int fd;
    char *line;
    char *s;
    int *data;
} mlxf;

int    *mlx_data_xpm(char *path,int fd,int *data);
void     xpm_skip_header(int fd);
void    get_data_xpm(int fd,int *data);
int     xpmidcolor(int fd,int *data,xpmcolordata     *idcolor);
char    *xpmimgdata(int fd,int *data);
int convert(char *s,xpmcolordata  *idcolor,int *data, int i);
int *xpmtoint(char *imgs,int *data,xpmcolordata  *idcolor);
int		ft_iswhitespace(char const c);
int ft_atoi_base(const char *str, int str_base);
int	base(int c, int base);
void    ft_error(char *str);
void    save_bitmap(unsigned int *color, int width, int height, int fd);
void recup(char *line, parse *pars);
char    *parsetex(char *line,int n);
doubleint    parsesize(char *line,int n);
int    parsecolor(char *line,int n);
void    sort_sprite(sprite **sprites,int posX,int posY,int size);
sprite **get_sprites(t_list *lst,parse *pars);
int     close_map(parse *pars, int i, int j);
int checkmap(parse *pars,t_list **lst);
char **ft_lstdtab(t_list *lst);
t_list    *recupmap(int fd, char *line);
void init_pars(parse *pars);
parse *cub_skip_header(int fd);
int     tab_width(char **tab);
void    create_charcub(char **tab,int width);
#endif