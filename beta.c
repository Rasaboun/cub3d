#include "raycast.h"

void init_texture(texture *texture, parse *pars,int *endian,int *bits,int *size_line,void *img)
{
	int fd;
	int data[4];



	texture[0].path = pars->ea;
	texture[1].path = pars->no;
	texture[2].path = pars->we;
	texture[3].path = pars->so;
	texture[4].path = pars->s;
	int i;
	i = 0;
	//for (int i = 0; i < 5; i++)
	//{
		fd = open(texture[i].path, O_RDONLY);
		if (fd < 1)
		{
			ft_putstr_fd("ERROR OPEN FILE", 1);
			exit(EXIT_FAILURE);
		}
		img = mlx_xpm_file_to_image(texture[i].mlx,texture[i].path, &texture[i].textwidth, &texture[i].textheight);
		texture[i].imagedata = (int *)mlx_get_data_addr(img,bits,size_line,endian);
		printf("size_line %d",*size_line);
		close(fd);
	//}
}

int main()
{
	parse *pars;
	int fdd;

	fdd = open("/home/user42/Bureau/cub3d/map.cub", O_RDWR);
	if (fdd > 0)
		pars = cub_skip_header(fdd);

	void *screenB;
	 int *imagescreenB;
	void *mlx;
	mlx = mlx_init();

	int bpp;
	int size_line;
	int endian;
	void *img;

	texture texture[5];
		texture[0].mlx = mlx;
	texture[1].mlx = mlx;
	texture[2].mlx = mlx;
	texture[3].mlx = mlx;
	texture[4].mlx = mlx;
	init_texture(texture, pars,&endian,&bpp,&size_line,img);

}
