
#include "raycast.h"
#include "test.h"

void put_pixel(int color, int *imagescreenB, int x, int y, int ratio_x, int ratio_y, int screenwidth)
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
			imagescreenB[y * screenWidth + x] = color;
			x++;
			xx++;
		}
		y++;
		yy++;
	}
}

void mini_map(int *imagescreenB, int screenwidth, int screenheight, int mapwidth, int mapheight, char **tab, int plx, int ply)
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

	width = screenWidth / 8;
	height = screenHeight / 8;

	size_x = width - margel; //158
	size_y = height - marget;

	ratio_x = size_x / mapwidth;
	ratio_y = size_y / mapheight;


	ii = 0;
	i = 0;
	y = 0;
	yy = 0;
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
			put_pixel(color, imagescreenB, ii, yy, ratio_x, ratio_y, screenwidth);
			ii += ratio_x;
			i++;
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

	width = screenWidth / 5;
	height = screenHeight / 17;

	size_x = width - margel; //158
	size_y = height - marget;

	ratio_x = size_x / mapwidth;
	ratio_y = size_y / mapheight;


	ii = 500;
	i = 0;
	y = 0;
	yy = 15;
		while (y < mapheight)
	{
		i = 0;
		ii = 500;
		while (i < mapwidth)
		{
			color = 0xc21316;//0xc21316;
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
		close(fd);
	}
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

	void *screenB;
	int *imagescreenB;
	void *mlx;
	mlx = mlx_init();

	void *mlx_win;
	screenB = mlx_new_image(mlx, screenWidth, screenHeight);
	int bpp;
	int size_line;
	int endian;
	void *img;
	imagescreenB = (unsigned int *)mlx_get_data_addr(screenB, &bpp, &size_line, &endian);

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
	double planeX = 0.0;
	double planeY = -0.66;
	int w = screenWidth;
	int h = screenHeight;
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

	if (argc >= 3 && ft_strcmp(argv[2],"--save") == 0)
	{
	int fd;
	fd = 0;
	fd = open("image.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 777);
	if (fd > 0)
		{
			param.save = 1;
			raycast(&param);
			save_bitmap(param.imagescreenB,screenWidth,screenHeight,fd);
			exit(1);
		}
	}
	mlx_win = mlx_new_window(mlx, screenWidth, screenHeight, "Raycasting!");
	param.mlx_win = mlx_win;

	mlx_hook(mlx_win, KEY_PRESSED, 1L << 0, deal_key, &param);
	mlx_loop_hook(mlx, raycast, &param);
	mlx_loop(mlx);
}
int deal_key(int key, void *param)
{
	raycasting *ray = (raycasting *)param;
	mlx_clear_window(ray->mlx, ray->mlx_win);

	if (key == 65361)
	{
		if (ray->pars->tab[(int)ray->posX][(int)(ray->posY - ray->planeY * 0.10)] == '0')
			ray->posY -= ray->planeY * 0.10;
		if (ray->pars->tab[(int)(ray->posX - ray->planeX * 0.10)][(int)ray->posY] == '0')
			ray->posX -= ray->planeX * 0.10;
	}
	if (key == 65363)
	{
		if (ray->pars->tab[(int)ray->posX][(int)(ray->posY + ray->planeY * 0.10)] == '0')
			ray->posY += ray->planeY * 0.10;
		if (ray->pars->tab[(int)(ray->posX + ray->planeX * 0.10)][(int)ray->posY] == '0')
			ray->posX += ray->planeX * 0.10;
	}
	if (key == 65362)
	{
		if (ray->pars->tab[(int)(ray->posX + ray->dirX * 0.10)][(int)ray->posY] == '0')
			ray->posX += ray->dirX * 0.10;
		if (ray->pars->tab[(int)ray->posX][(int)(ray->posY + ray->dirY * 0.10)] == '0')
			ray->posY += ray->dirY * 0.10;
	}
	if (key == 65364)
	{
		if (ray->pars->tab[(int)(ray->posX - ray->dirX * 0.10)][(int)ray->posY] == '0')
			ray->posX -= ray->dirX * 0.10;
		if (ray->pars->tab[(int)ray->posX][(int)(ray->posY - ray->dirY * 0.10)] == '0')
			ray->posY -= ray->dirY * 0.10;
	}
	if (key == 100)
	{
		double oldDirX = ray->dirX;
		double oldPlaneX = ray->planeX;
		ray->dirX = ray->dirX * cos(-0.10) - ray->dirY * sin(-0.10);
		ray->dirY = oldDirX * sin(-0.10) + ray->dirY * cos(-0.10);
		ray->planeX = ray->planeX * cos(-0.10) - ray->planeY * sin(-0.10);
		ray->planeY = oldPlaneX * sin(-0.10) + ray->planeY * cos(-0.10);
	}
	if (key == 113)
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
		if (fdd > 0)
			save_bitmap(ray->imagescreenB, screenWidth, screenHeight, fdd);
		mlx_destroy_window(ray->mlx, ray->mlx_win);
		freeall(ray->pars);
		exit(EXIT_SUCCESS);
	}
	return 1;
}

int raycast(raycasting *ray)
{

	double zbuffer[screenWidth];
	for (int n = 0; n < (screenWidth * screenHeight); n++)
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
		double perpWallDist;

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
			perpWallDist = (mapX - ray->posX + (1 - stepX) / 2) / raydirX;
		else
			perpWallDist = (mapY - ray->posY + (1 - stepY) / 2) / raydirY;

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
			ray->imagescreenB[(screenWidth)*begin + x] = ray->pars->c;
		}
		for (int end = drawEnd; end < ray->h; end++)
		{
			ray->imagescreenB[(screenWidth)*end + x] = ray->pars->f;
		}
		for (int y = drawStart; y < drawEnd; y++)
		{
			int texY = (int)texPos & (ray->texture[side].textheight - 1);

			texPos += step;
			int color = ray->texture[side].imagedata[ray->texture[side].textheight * texY + ray->texture[side].textwidth - texX];
			if (color != -1)
				ray->imagescreenB[(screenWidth)*y + x] = color;
		}
		zbuffer[x] = perpWallDist;
	}
	int i = 0;
	while (ray->pars->sprites[i])
		i++;
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
					if (colors != -1)
						ray->imagescreenB[(screenWidth)*yy + stripe] = colors;
				}
		}
	}
	mini_map(ray->imagescreenB, screenWidth, screenHeight, ray->pars->width, ray->pars->height, ray->pars->tab, (int)ray->posX, (int)ray->posY);
	mini_life(ray->imagescreenB, screenWidth, screenHeight, ray->pars->hwidth, ray->pars->hheight,ray->pars->tabhud);

	if(ray->save == 0)
		mlx_put_image_to_window(ray->mlx, ray->mlx_win, ray->screenB, 0, 0);
	return (1);
}
