#include <stdlib.h>
#include <math.h>
#include <mlx.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <mlx.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int	main()
{


void *screenB;
	unsigned int *imagescreenB;
	void *mlx;
		void*img;

	//void *mlx_win;
	mlx = mlx_init();
	//mlx_win = mlx_new_window(mlx, 900, 600, "Raycasting!");
	//screenB = mlx_new_image(mlx, 900, 600);*/
	int bpp;
	int size_line;
	int endian;
	//imagescreenB = (unsigned int *)mlx_get_data_addr(screenB, &bpp, &size_line, &endian);
	int *addr;
	int fd;
	int data[4];
char *tex = "/home/user42/Bureau/cub3d/texture/open.xpm";
	int l;
	int la;

img = mlx_xpm_file_to_image(mlx,"/home/user42/Bureau/cub3d/texture/open.xpm",&l,&la);
	addr = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
	printf("%d",addr[0]);

	//mlx_loop(mlx);

}
