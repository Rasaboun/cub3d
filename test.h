#include <stdlib.h>
#include <math.h>
#include <mlx.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft/libft.h"

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