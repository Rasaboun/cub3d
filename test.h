#ifndef TEST_H

#define TEST_H

#define XPMCOMMENT "/* columns rows colors chars-per-pixel */"
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
    int    alr;
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

typedef struct rgbcolor
{
    int r;
    int g;
    int b;
    int rgb;
}rgbcolor;

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
    int width;
    int height;
    int hwidth;
    int hheight;
    char **tabhud;
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

typedef struct cub_skip
{
    char *line;
    int n;
    t_list *first;
    parse *pars;
    t_list *lst;
    sprite **sprites;
    t_list *hud;
    int hudrep;
} cub_skip;

typedef struct checkmap
{
    int		linecount;
	int		i;
	int		j;
	char	mapf;
	int		player;
	char	*play;
	sprite	*sprites;
	t_list	*new;
} t_checkmap;


void	freecubskip(cub_skip *map_pars);
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
void    ft_error(char *str,parse *pars);
int    save_bitmap(unsigned int *color, int width, int height, int fd);
int	save_bmp(int width, unsigned int *color, int i, int fd);
void recup(char *line, parse *pars);
char    *parsetex(char *line,int n);
doubleint    parsesize(char *line,int n);
int    parsecolor(char *line,int n);
void    sort_sprite(sprite **sprites,int posX,int posY,int size);
void get_sprites(cub_skip *map_pars);
int     close_map(parse *pars, int i, int j);
int checkmap(parse *pars,t_list **lst);
char **ft_lstdtab(t_list *lst);
 t_list    *recupmap(int fd, char *line,cub_skip *map_pars);
void init_pars(parse *pars);
parse *cub_skip_header(int fd);
int     tab_width(char **tab);
void    create_charcub(char **tab,int width);
void    get_map(int fd,cub_skip *map_pars);
	void	ft_swap_sprite(sprite **one,int j);
	int	ft_while(char *s3, const char *s1, int i);
char	*ft_strjoinzero(char *s1, int size);
	void	ft_swap_sprite(sprite **one, int j);
	int	ft_calcul_dist(int x, int y, int posx, int posy);
void	get_sprites(cub_skip *map_pars);
void	freesprite(parse *pars);
int		ft_getelemmap(parse *pars, t_checkmap *ck, t_list **lst);
void	ft_getspritemap(t_checkmap *ck, t_list **lst);
void	ft_getplayermap(parse *pars, t_checkmap *ck);
void	freepars(parse *pars);
int		tab_height(char **tab);
void	duplicerror(char *s, parse *pars);
t_list	*recupmap(int fd, char *line, cub_skip *map_pars);
t_list	*recuphud(int fd, char *line, cub_skip *map_pars);
int	skip_wspace(char *s);
void	ft_rerror(cub_skip *map_pars, t_list *first, char *line, char *str);
void	freemap(parse *pars);
void	freehud(parse *pars);
void	freesprite(parse *pars);
void	freetext(parse *pars);
void    init_map_pars(cub_skip *map_pars);
void	file_headers(unsigned char *file_header, int file_size, \
int width,unsigned char *image_header);
int	save_bmp(int width, unsigned int *color, int i, int fd);
#endif
