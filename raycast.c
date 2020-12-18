
#include "raycast.h"
#include "test.h"

void put_pixel(int color, int *imagescreenb, int x, int y, int ratio_x, int ratio_y, int screenx)
{
	int yy;
	int xx;
	int xtmp;
	xx = 0;
	yy = 0;
	xtmp = x;

	while (yy < ratio_y)
	{
		xx = 0;
		x = xtmp;
		while (xx < ratio_x)
		{
			imagescreenb[y * screenx + x] = color;
			x++;
			xx++;
		}
		y++;
		yy++;
	}
}

void mini_map(int *imagescreenb, int screenx, int screeny, int mapwidth, int mapheight, char **tab, int plx, int ply,sprite **sprit)
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
	margel = screenx / (16 * 2);
	marget = screeny / (16 * 2);

	width = screenx / 8;
	height = screeny / 8;

	size_x = width - margel;
	size_y = height - marget;

	ratio_x = size_x / mapwidth;
	ratio_y = size_y / mapheight;


	ii = 0;
	i = 0;
	y = 0;
	yy = 0;
	sp = 0;
		while (y < mapheight)
	{
		i = 0;
		ii = 0;
		while (i < mapwidth)
		{
			if (y == plx && i == ply)
			{
				color = 0xfc030b;
			}
			else if (tab[y][i] != '1')
				color = 0x292d2e;
			else
				color = 0x33dcf2;
			while(sprit != NULL && sprit[sp] != NULL)
			{
				if (y == sprit[sp]->x && i == sprit[sp]->y)
					color = 0xffffff;
				sp++;
			}
			put_pixel(color, imagescreenb, ii, yy, ratio_x, ratio_y, screenx);
			ii += ratio_x;
			i++;
			sp = 0;
		}
		yy += ratio_y;
		y++;
	}
}

void mini_life(int *imagescreenb, int screenwidth, int screenheight, int mapwidth, int mapheight,char **tab)
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
	void *screenB;

	if(tab == NULL)
		return ;
	margel = screenwidth / (16 * 2);
	marget = screenheight / (16 * 2);

	width = screenwidth / 5;
	height = screenheight / 17;

	size_x = width - margel;
	size_y = height - marget;

	ratio_x = size_x / mapwidth;
	ratio_y = size_y / mapheight;


	ii = screenwidth/3;
	i = 0;
	y = 0;
	yy = 15;
		while (y < mapheight)
	{
		i = 0;
		ii = screenwidth/3;
		while (i < mapwidth)
		{
			color = 0xc21316;
			if (tab[y][i] == '4' || tab[y][i] == '6')
			put_pixel(color, imagescreenb, ii, yy, ratio_x, ratio_y, screenwidth);
			ii += ratio_x;
			i++;
		}
		yy += ratio_y;
		y++;
	}
}

void freeall(parse *pars)
{
	freepars(pars);
}
void init_texture(texture *texture, parse *pars,void *mlx)
{
	int fd;
	int i;

	i = 0;
	texture[0].path = pars->no;
	texture[1].path = pars->ea;
	texture[2].path = pars->we;
	texture[3].path = pars->so;
	texture[4].path = pars->s;
	fd  = 0;
	while (i < 5)
	{
		if(texture[i].path == NULL)
			ft_error("ERROR OPEN FILE NULL PATH", pars);
		if((fd = open(texture[i].path, O_RDONLY)) <= 0)
			ft_error("ERROR OPEN FILE", pars);
		close(fd);
		if((texture[i].img = mlx_xpm_file_to_image(mlx, texture[i].path, &texture[i].textwidth, &texture[i].textheight)) == NULL)
			ft_error("Error xpm to file",pars);

		if( (texture[i].imagedata = (int *)mlx_get_data_addr(texture[i].img, &texture[i].bpp, &texture[i].size_line, &texture[i].endian)) == NULL)
			ft_error("Error xpm to file",pars);
		i++;
	}
}

int ft_checkun(parse *pars)
{
	if (pars->r.i == 0)
		ft_error("error resolution",pars);
	if (pars->r.ii == 0)
		ft_error("error resolution",pars);	
	if(pars->c == -1 || pars->f == -1)
		ft_error("error color",pars);

}

int main(int argc, char *argv[])
{
	parse *pars;
	int fdd;
	void *screenB;
	int *imagescreenb;
	void *mlx;
	int screenx;
	int screeny;
	int w;
	int h;
	void *mlx_win;
	int bpp;
	int size_line;
	int endian;
	void *img;
	texture texture[5];
	double posx;
	double posy;
	double dirx;
	double diry;
	double planey;
	double planex;
	int fd;
	fd = 0;
	if (argc >= 2)
	{
		fdd = open(argv[1], O_RDWR);
		if (fdd > 0)
			pars = cub_skip_header(fdd);
		else
		{
			ft_putstr_fd("Error open .cub file",1);
		}
	}
	else
	{
		ft_putstr_fd("error ARG",1);
		exit(0);
	}

	ft_checkun(pars);
	
	mlx = mlx_init();
	
	mlx_get_screen_size(mlx, &screenx, &screeny);
	
	
	if(pars->r.i > screenx)
		pars->r.i = screenx;
	if(pars->r.ii > screeny)
		pars->r.ii = screeny;
	w = pars->r.i;
	h = pars->r.ii;

	screenB = mlx_new_image(mlx, pars->r.i, pars->r.ii);

	if ((imagescreenb = (unsigned int *)mlx_get_data_addr(screenB, &bpp, &size_line, &endian)) == NULL)
		ft_putstr_fd("get data addr screen",1);
	
	init_texture(texture, pars,mlx);

	posx = (float)pars->play.x;
	posy = (float)pars->play.y;
	dirx = 1.0;
	diry = 0.0;
	planex = 0.0;
	planey = -0.66;

	if (pars->play.direction == 'E')
	{
		planey = 0.0;
		planex = 0.66;
		dirx = 0.0;
		diry = 1;
	}
	if (pars->play.direction == 'W')
	{
		planey = 0.0;
		planex = -0.66;
		dirx = 0.0;
		diry = -1;
	}
	if (pars->play.direction == 'S')
	{
		planey = -0.66;
		planex = 0.0;
		dirx = 1.0;
		diry = 0.0;
	}
	if (pars->play.direction == 'N')
	{
		planey = 0.66;
		planex = 0.0;
		dirx = -1.0;
		diry = 0.0;
	}
	raycasting param;
	param.posy = posy+0.5;
	param.posx = posx+0.5;
	param.dirx = dirx;
	param.diry = diry;
	param.planey = planey;
	param.planex = planex;
	param.w = w;
	param.h = h;
	param.mlx = mlx;
	param.imagescreenb = imagescreenb;
	param.screenB = screenB;
	param.size_line = size_line;
	param.texture = texture;
	param.pars = pars;
	param.left = 0;
	param.right = 0;
	param.rotate_right = 0;
	param.rotate_left = 0;
	param.back = 0;
	param.forward = 0;
	param.save = 0;
	if (argc >= 3 && ft_strcmp(argv[2],"--save") == 0)
	{
		if ((fd = open("image.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 777)) > 0)
		{
			param.save = 1;
			raycast(&param);
			save_bitmap(param.imagescreenb,param.w,param.h,fd);
			
			freeall(pars);
			close(fd);
			exit(1);
		}
	else
		ft_error("Error create save img",pars);
	
	}

	mlx_win = mlx_new_window(mlx, param.w, param.h, "Rasaboun Raycasting !");
	param.mlx_win = mlx_win;
	mlx_hook(mlx_win, 2, 1L << 0, ft_key_press, &param);
	mlx_hook(mlx_win, 3, 1L << 1, ft_key_release, &param);
	mlx_loop_hook(mlx, raycast, &param);
	mlx_loop(mlx);
}


int raycast(raycasting *ray)
{

	if(ray->right == 1)
		move_right(ray);
	if(ray->left == 1)
		move_left(ray);
		if(ray->back == 1)
		move_back(ray);
	if(ray->forward == 1)
		move_forward(ray);
			if(ray->rotate_left == 1)
		turn_left(ray);
	if(ray->rotate_right == 1)
		turn_right(ray);

	double zbuffer[ray->w];
	for (int n = 0; n < (ray->w * ray->h); n++)
	{
		ray->imagescreenb[n] = 0;
	}
	for (int x = 0; x < ray->w; x++)
	{
		ft_dda(ray,x);
		ft_draw(ray,x,zbuffer);
	}

	int i = 0;
	while (ray->pars->sprites != NULL && ray->pars->sprites[i] != NULL)
		i++;

	if(i != 0)
	{
	sort_sprite(ray->pars->sprites, ray->posx, ray->posy, i);
	for (int y = 0; y < i; y++)
	{
		ft_draw_sprites(ray,y,zbuffer);
	}
	}
	mini_map(ray->imagescreenb, ray->w, ray->h, ray->pars->width, ray->pars->height, ray->pars->tab, (int)ray->posx, (int)ray->posy,ray->pars->sprites);
	mini_life(ray->imagescreenb, ray->w, ray->h, ray->pars->hwidth, ray->pars->hheight,ray->pars->tabhud);

	if(ray->save == 0)
	{
		mlx_clear_window(ray->mlx,ray->mlx_win);
		mlx_put_image_to_window(ray->mlx, ray->mlx_win, ray->screenB, 0, 0);
	}
	return (1);
}
