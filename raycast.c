
#include "raycast.h"
#include "test.h"

void put_pixel(int color, int *imagescreenB, int x, int y, int ratio_x, int ratio_y, int screenx)
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
			imagescreenB[y * screenx + x] = color;
			x++;
			xx++;
		}
		y++;
		yy++;
	}
}

void mini_map(int *imagescreenB, int screenx, int screeny, int mapwidth, int mapheight, char **tab, int plx, int ply,sprite **sprit)
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
	int sp;
	margel = screenx / (16 * 2);
	marget = screeny / (16 * 2);

	width = screenx / 8;
	height = screeny / 8;

	size_x = width - margel; //158
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
			while(sprit[sp] != NULL)
			{
				if (y == sprit[sp]->y && i == sprit[sp]->x)
					color = 0xffffff;
				sp++;
			}
			put_pixel(color, imagescreenB, ii, yy, ratio_x, ratio_y, screenx);
			ii += ratio_x;
			i++;
			sp = 0;
		}
		yy += ratio_y;
		y++;
	}
}

void mini_life(int *imagescreenB, int screenwidth, int screenheight, int mapwidth, int mapheight,char **tab)
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

	margel = screenwidth / (16 * 2);
	marget = screenheight / (16 * 2);

	width = screenwidth / 5;
	height = screenheight / 17;

	size_x = width - margel; //158
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
			put_pixel(color, imagescreenB, ii, yy, ratio_x, ratio_y, screenwidth);
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
void init_texture(texture *texture, parse *pars)
{
	int fd;
	int data[4];

	texture[0].path = pars->ea;
	texture[1].path = pars->no;
	texture[2].path = pars->we;
	texture[3].path = pars->so;
	texture[4].path = pars->s;

	for (int i = 0; i < 5; i++)
	{
		fd = open(texture[i].path, O_RDONLY);
		if (fd < 1)
		{
			ft_putstr_fd("ERROR OPEN FILE", 1);
			exit(EXIT_FAILURE);
		}
		texture[i].img = mlx_xpm_file_to_image(texture[i].mlx, texture[i].path, &texture[i].textwidth, &texture[i].textheight);
		if (texture[i].img == NULL)
			printf("NO %d", i);
		texture[i].imagedata = (int *)mlx_get_data_addr(texture[i].img, &texture[i].bpp, &texture[i].size_line, &texture[i].endian);
		if(texture[i].imagedata == NULL)
		{
			printf("error text");
			exit(0);
		}
		close(fd);
	}
}

int ft_checkun(parse *pars)
{
	if (pars->r.i == 0)
		ft_error("error resolution");
	if (pars->r.ii == 0)
		ft_error("error resolution");	
	if(pars->c == -1 || pars->f == -1)
		ft_error("error color");

}

int main(int argc, char *argv[])
{
	parse *pars;
	int fdd;


	if (argc >= 2)
		{
			fdd = open(argv[1], O_RDWR);

		}
	else
	{
		exit(0);
	}
	if (fdd > 0)
		pars = cub_skip_header(fdd);
	ft_checkun(pars);
	void *screenB;
	int *imagescreenB;
	void *mlx;
	mlx = mlx_init();
	int screenx;
	int screeny;
	mlx_get_screen_size(mlx, &screenx, &screeny);
	
	
	if(pars->r.i > screenx)
		pars->r.i = screenx;
		if(pars->r.ii > screeny)
		pars->r.ii = screeny;
		int w = pars->r.i;
	int h = pars->r.ii;
	void *mlx_win;
	screenB = mlx_new_image(mlx, pars->r.i, pars->r.ii);
	int bpp;
	int size_line;
	int endian;
	void *img;
	imagescreenB = (unsigned int *)mlx_get_data_addr(screenB, &bpp, &size_line, &endian);
	if(imagescreenB == NULL)
	{
		exit(0);
	}
	texture texture[5];
	texture[0].mlx = mlx;
	texture[1].mlx = mlx;
	texture[2].mlx = mlx;
	texture[3].mlx = mlx;
	texture[4].mlx = mlx;
	init_texture(texture, pars);

	double posX = (float)pars->play.x;
	double posY = (float)pars->play.y;
	double dirX = 1.0;
	double dirY = 0.0;
	double planeX = 0.0; //N = dirx = 0 planex -0.66 dirY = -1 planeY 0
	double planeY = -0.66; //S dirx = 0 playx 0.66 dir y 1 planeY 0
	// O dirx = 1 planex 0 diry = 0 planey = -0.66
	 // E dirx = -1 planex = 0 diry 0 planey 0.66

	if (pars->play.direction == 'E')
	{
		planeY = 0.0;
		planeX = 0.66;
		dirX = 0.0;
		dirY = 1;
	}
	if (pars->play.direction == 'O')
	{
		planeY = 0.0;
		planeX = -0.66;
		dirX = 0.0;
		dirY = -1;
	}
	if (pars->play.direction == 'S')
	{
		planeY = -0.66;
		planeX = 0.0;
		dirX = 1.0;
		dirY = 0.0;
	}
	if (pars->play.direction == 'N')
	{
		planeY = 0.66;
		planeX = 0.0;
		dirX = -1.0;
		dirY = 0.0;
	}
	raycasting param;
	param.posY = posY;
	param.posX = posX;
	param.dirX = dirX;
	param.dirY = dirY;
	param.planeY = planeY;
	param.planeX = planeX;
	param.w = w;
	param.h = h;
	param.mlx = mlx;
	param.imagescreenB = imagescreenB;
	param.screenB = screenB;
	param.size_line = size_line;
	param.texture = texture;
	param.pars = pars;
	if(argc >= 3)
	{
	if(ft_strcmp(argv[2],"--save") == 0)
	{
		param.save = 1;
	}
	else
	{
		param.save = 0;
	}
	}
	

	if (argc >= 3 && ft_strcmp(argv[2],"--save") == 0)
	{
	int fd;
	fd = 0;
	fd = open("image.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 777);
	if (fd > 0)
		{
			param.save = 1;
			raycast(&param);
			save_bitmap(param.imagescreenB,param.w,param.h,fd);
			exit(1);
		}
	}
	mlx_win = mlx_new_window(mlx, param.w, param.h, "Raycasting!");
	param.mlx_win = mlx_win;

	mlx_hook(mlx_win, KEY_PRESSED, 1L << 0, deal_key, &param);
	mlx_loop_hook(mlx, raycast, &param);
	mlx_loop(mlx);
}
int deal_key(int key, void *param)
{
	raycasting *ray = (raycasting *)param;
	mlx_clear_window(ray->mlx, ray->mlx_win);

	if (key == 	97)//q
	{
		if (ray->pars->tab[(int)ray->posX][(int)(ray->posY - ray->planeY * 0.10)] == '0')
			ray->posY -= ray->planeY * 0.10;
		if (ray->pars->tab[(int)(ray->posX - ray->planeX * 0.10)][(int)ray->posY] == '0')
			ray->posX -= ray->planeX * 0.10;
			
	}
	if (key == 	100)//d
	{
		if (ray->pars->tab[(int)ray->posX][(int)(ray->posY + ray->planeY * 0.10)] == '0')
			ray->posY += ray->planeY * 0.10;
		if (ray->pars->tab[(int)(ray->posX + ray->planeX * 0.10)][(int)ray->posY] == '0')
			ray->posX += ray->planeX * 0.10;

		
	}
	if (key == 119)//w
	{
		if (ray->pars->tab[(int)(ray->posX + ray->dirX * 0.10)][(int)ray->posY] == '0')
			ray->posX += ray->dirX * 0.10;
		if (ray->pars->tab[(int)ray->posX][(int)(ray->posY + ray->dirY * 0.10)] == '0')
			ray->posY += ray->dirY * 0.10;
		
	}
	if (key == 	115) //s
	{
		if (ray->pars->tab[(int)(ray->posX - ray->dirX * 0.10)][(int)ray->posY] == '0')
			ray->posX -= ray->dirX * 0.10;
		if (ray->pars->tab[(int)ray->posX][(int)(ray->posY - ray->dirY * 0.10)] == '0')
			ray->posY -= ray->dirY * 0.10;
	}
	if (key == 65363)//fleche gauche
	{
		double oldDirX = ray->dirX;
		double oldPlaneX = ray->planeX;
		ray->dirX = ray->dirX * cos(-0.10) - ray->dirY * sin(-0.10);
		ray->dirY = oldDirX * sin(-0.10) + ray->dirY * cos(-0.10);
		ray->planeX = ray->planeX * cos(-0.10) - ray->planeY * sin(-0.10);
		ray->planeY = oldPlaneX * sin(-0.10) + ray->planeY * cos(-0.10);
	}
	if (key == 65361)//fleche droite
	{
		double oldDirX = ray->dirX;
		ray->dirX = ray->dirX * cos(0.10) - ray->dirY * sin(0.10);
		ray->dirY = oldDirX * sin(0.10) + ray->dirY * cos(0.10);
		double oldPlaneX = ray->planeX;
		ray->planeX = ray->planeX * cos(0.10) - ray->planeY * sin(0.10);
		ray->planeY = oldPlaneX * sin(0.10) + ray->planeY * cos(0.10);
	}
	if (key == 65307)
	{
		int fdd;
		fdd = 0;
		fdd = open("image.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 777);
		if (fdd > 0 && ray->save == 1)
			save_bitmap(ray->imagescreenB, ray->w, ray->h, fdd);
		mlx_destroy_window(ray->mlx, ray->mlx_win);
		freeall(ray->pars);
		exit(EXIT_SUCCESS);
	}
	return 1;
}

int raycast(raycasting *ray)
{

	double zbuffer[ray->w];
	for (int n = 0; n < (ray->w * ray->h); n++)
	{
		ray->imagescreenB[n] = 0;
	}
	for (int x = 0; x < ray->w; x++)
	{
		double cameraX = 2 * x / (double)ray->w - 1;
		double raydirX = ray->dirX + ray->planeX * cameraX;
		double raydirY = ray->dirY + ray->planeY * cameraX;

		int mapX = (int)ray->posX;
		int mapY = (int)ray->posY;

		double sideDistX;
		double sideDistY;

		double deltaDistX = (raydirY == 0) ? 0 : ((raydirX == 0) ? 1 : fabs(1 / raydirX));
		double deltaDistY = (raydirX == 0) ? 0 : ((raydirY == 0) ? 1 : fabs(1 / raydirY));
		float perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;

		if (raydirX < 0)
		{
			stepX = -1;
			sideDistX = (ray->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - ray->posX) * deltaDistX;
		}
		if (raydirY < 0)
		{
			stepY = -1;
			sideDistY = (ray->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - ray->posY) * deltaDistY;
		}

		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (ray->pars->tab[mapX][mapY] == '1')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (double)(mapX - ray->posX + (1 - stepX) / 2) / raydirX;
		else
			perpWallDist = (double)(mapY - ray->posY + (1 - stepY) / 2) / raydirY;

		if (perpWallDist <= 0.0)
			perpWallDist = 1;
		int lineHeight = (int)(ray->h / perpWallDist);
		int drawStart = -lineHeight / 2 + ray->h / 2;

		if (drawStart < 0)
			drawStart = 0;

		int drawEnd = lineHeight / 2 + ray->h / 2;

		if (drawEnd >= ray->h)
			drawEnd = ray->h - 1;
		int charint = (ray->pars->tab[mapX][mapY] - 48);
		int texNum = charint - 1;
		double wallX;

		if (side == 0)
			wallX = ray->posY + perpWallDist * raydirY;
		else
			wallX = ray->posX + perpWallDist * raydirX;

		if (side == 0 && raydirX > 0)
			side = 3;
		if (side == 1 && raydirY < 0)
			side = 2;
		wallX -= floor((wallX));
		int texX = (int)(wallX * (double)(ray->texture[side].textwidth));

		if (side == 0)
			texX = ray->texture[side].textwidth - texX - 1;
		if (side == 1)
			texX = ray->texture[side].textwidth - texX - 1;

		double step = 1.0 * ray->texture[side].textwidth / lineHeight;
		double texPos = (drawStart - ray->h / 2 + lineHeight / 2) * step;

		for (int begin = 0; begin < drawStart; begin++)
		{
			ray->imagescreenB[(ray->w)*begin + x] = ray->pars->c;
		}

		for (int end = drawEnd; end < ray->h; end++)
		{
			ray->imagescreenB[(ray->w)*end + x] = ray->pars->f;
		}
		for (int y = drawStart; y < drawEnd; y++)
		{
			int texY = (int)texPos & (ray->texture[side].textheight - 1);

			texPos += step;
			int color = ray->texture[side].imagedata[ray->texture[side].textheight * texY + ray->texture[side].textwidth - texX];
			if (color != -1)
				ray->imagescreenB[(ray->w)*y + x] = color;
		}
		zbuffer[x] = perpWallDist;
	}

	int i = 0;
	while (ray->pars->sprites != NULL && ray->pars->sprites[i] != NULL)
		i++;

	if(i != 0)
	{
	sort_sprite(ray->pars->sprites, ray->posX, ray->posY, i);
	for (int y = 0; y < i; y++)
	{
		double spriteX = (ray->pars->sprites[y]->x + 0.5)- ray->posX;
		double spriteY = (ray->pars->sprites[y]->y + 0.5)- ray->posY;
		double invDet = 1.0 / (ray->planeX * ray->dirY - ray->dirX * ray->planeY);
		double transformX = invDet * (ray->dirY * spriteX - ray->dirX * spriteY);
		double transformY = invDet * (-ray->planeY * spriteX + ray->planeX * spriteY);

		double spriteScreenX = ((ray->w / 2) * (1 + transformX / transformY));

		int spriteHeight = abs((int)(ray->h / (transformY)));
		int drawStartY = -spriteHeight / 2 + ray->h / 2;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + ray->h / 2;
		if (drawEndY >= ray->h)
			drawEndY = ray->h - 1;

		int spriteWidth = abs((int)(ray->h / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= ray->w)
			drawEndX = ray->w - 1;

		for (int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * ray->texture[4].textwidth / spriteWidth) / 256;
			if (transformY > 0 && stripe > 0 && stripe < ray->w && transformY < zbuffer[stripe])
				for (int yy = drawStartY; yy < drawEndY; yy++)
				{
					int d = (yy)*256 - ray->h * 128 + spriteHeight * 128;
					int texY = ((d * ray->texture[4].textheight) / spriteHeight) / 256;
					int colors = ray->texture[4].imagedata[ray->texture[4].textheight * texY + texX];
					if ((colors  & (0xFF << 24)) == 0)
						ray->imagescreenB[(ray->w)*yy + stripe] = colors;
				}
		}
	}
	}
	mini_map(ray->imagescreenB, ray->w, ray->h, ray->pars->width, ray->pars->height, ray->pars->tab, (int)ray->posX, (int)ray->posY,ray->pars->sprites);
	mini_life(ray->imagescreenB, ray->w, ray->h, ray->pars->hwidth, ray->pars->hheight,ray->pars->tabhud);

	if(ray->save == 0)
		mlx_put_image_to_window(ray->mlx, ray->mlx_win, ray->screenB, 0, 0);
	return (1);
}
