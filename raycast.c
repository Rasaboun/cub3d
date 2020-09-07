
#include "raycast.h"
#include "test.h"

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1},
  {1,0,0,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
void freeall(texture *texture)
{
    int i;
    i = 0;

    while (i<4)
    {
        free(texture[i].imagedata);
        i++;
    }
}
void init_texture(texture *texture,char **path)
{
    int fd;
    int data[4];

    for(int i = 0;i < 4;i++)
    {
        texture[i].path = path[i];
        fd = open(texture[i].path,O_RDONLY);
        if (fd < 1)
        {
            ft_putstr_fd("ERROR OPEN FILE",1);
            exit(EXIT_FAILURE);
        }
        //texture[i].img = mlx_xpm_file_to_image(mlx,texture[i].path,&texture[i].textwidth,&texture[i].textheight);
        //texture[i].imagedata = (unsigned int*)mlx_get_data_addr(texture[i].img,&texture[i].bpp,&texture[i].size_line,&texture[i].endian);
        texture[i].imagedata = mlx_data_xpm(texture[i].path,fd,data);
        texture[i].textheight = data[0];
        texture[i].textwidth = data[1];
        close(fd);
    }
}
 
int main()
{
    void* screenB;
    unsigned int *imagescreenB;
    void    *mlx;
    void    *mlx_win;
    char *path[4] = {"/home/user42/Bureau/cub3d/texture/redbrick.xpm","/home/user42/Bureau/cub3d/texture/redbrick.xpm","/home/user42/Bureau/cub3d/texture/redbrick.xpm","/home/user42/Bureau/cub3d/texture/redbrick.xpm"};
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, screenWidth, screenHeight, "Raycasting!");
    screenB = mlx_new_image(mlx,screenWidth,screenHeight);
    int bpp;
    int size_line;
    int endian;
    imagescreenB = (unsigned int*)mlx_get_data_addr(screenB,&bpp,&size_line,&endian);
    texture texture[4];
    init_texture(texture,path);
    double posX = 2.5;
    double posY = 12.0;
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
    param.mlx_win = mlx_win;
    param.imagescreenB = imagescreenB;
    param.screenB = screenB;
    param.size_line = size_line;
    param.texture = texture;
    mlx_hook(mlx_win,KEY_PRESSED,1L << 0,deal_key,&param);
    mlx_loop_hook(mlx,raycast,&param);
    mlx_loop(mlx);
}
int deal_key(int key, void *param)
{
    raycasting *ray = (raycasting*)param;
    //down
    if (key == 65361)
    {
        if(worldMap[(int)ray->posX][(int)(ray->posY-ray->planeY * 0.10)] == 0) ray->posY -= ray->planeY * 0.10;
        if(worldMap[(int)(ray->posX-ray->planeX * 0.10)][(int)ray->posY] == 0) ray->posX -= ray->planeX * 0.10;
    }
        //up
    if (key == 65363)
    {
        if(worldMap[(int)ray->posX][(int)(ray->posY+ray->planeY * 0.10)] == 0) ray->posY += ray->planeY * 0.10;
        if(worldMap[(int)(ray->posX+ray->planeX * 0.10)][(int)ray->posY] == 0) ray->posX += ray->planeX * 0.10;
    }
        //right
    if (key == 65362)
    {
        if(worldMap[(int)(ray->posX + ray->dirX * 0.10)][(int)ray->posY] == 0) ray->posX += ray->dirX * 0.10;
        if(worldMap[(int)ray->posX][(int)(ray->posY+ray->dirY * 0.10)] == 0) ray->posY += ray->dirY * 0.10;
    }
        //left
    if (key == 65364)
    {
        if(worldMap[(int)(ray->posX - ray->dirX * 0.10)][(int)ray->posY] == 0) ray->posX -= ray->dirX * 0.10;
        if(worldMap[(int)ray->posX][(int)(ray->posY-ray->dirY * 0.10)] == 0) ray->posY -= ray->dirY * 0.10;
    }
    //rotate left
    if (key == 100)
    {
        double oldDirX = ray->dirX;
        double oldPlaneX = ray->planeX;
        ray->dirX = ray->dirX * cos(-0.10) - ray->dirY * sin(-0.10);
        ray->dirY = oldDirX * sin(-0.10) + ray->dirY * cos(-0.10);
        ray->planeX = ray->planeX * cos (-0.10) - ray->planeY * sin(-0.10);
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
        mlx_destroy_window(ray->mlx,ray->mlx_win);
        freeall(ray->texture);
        exit(EXIT_SUCCESS);
    }
        return 1;
}

int raycast(raycasting *ray)
{
    mlx_clear_window(ray->mlx,ray->mlx_win);
    double zbuffer[screenWidth];
    //clear
    for(int n = 0;n < (screenWidth*screenHeight);n++){ ray->imagescreenB[n] = 0;}
    //DDA
    for(int x = 0;x < ray->w;x++)
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
            if (worldMap[mapX][mapY] == 1) hit = 1;
        } 
        if (side == 0)
            perpWallDist = (mapX - ray->posX + (1 - stepX) / 2) / raydirX;
        else
            perpWallDist = (mapY - ray->posY + (1 - stepY) / 2) / raydirY;

        //choose Line height
        int lineHeight = (int)(ray->h / perpWallDist);
        int drawStart = -lineHeight / 2 + ray->h / 2;

        if(drawStart < 0)
            drawStart = 0;

        int drawEnd = lineHeight / 2 + ray->h / 2;

        if(drawEnd >= ray->h)
            drawEnd = ray->h - 1;

        //Texture
        int texNum = worldMap[mapX][mapY] - 1;
        double wallX;

        if (side == 0) wallX = ray->posY + perpWallDist * raydirY;
        else           wallX = ray->posX + perpWallDist * raydirX;

        if(side == 0 && raydirX > 0) side = 3;
        if(side == 1 && raydirY < 0) side = 2;
        wallX -= floor((wallX));
        int texX = (int)(wallX * (double)(ray->texture[side].textwidth));

        if(side == 0)  texX = ray->texture[side].textwidth - texX - 1 ;
        if(side == 1)  texX = ray->texture[side].textwidth - texX - 1 ;

        double step = 1.0 * ray->texture[side].textwidth / lineHeight;
        double texPos = (drawStart - ray->h / 2 + lineHeight / 2) * step;
        for(int begin = 0;begin <drawStart;begin++){ ray->imagescreenB[(screenWidth) * begin + x] = 0x0000FF;}
        for(int end = drawEnd;end < ray->h;end++){ ray->imagescreenB[(screenWidth) * end + x] = 0x008000;}
        for(int y = drawStart; y<drawEnd; y++)
        {
            int texY = (int)texPos & (ray->texture[side].textheight - 1);

            texPos += step;
            int color = ray->texture[side].imagedata[ray->texture[side].textheight * texY + ray->texture[side].textwidth -texX];
        //draw
            if(color != -1)ray->imagescreenB[(screenWidth) * y + x] = color;
        }
        zbuffer[x] = perpWallDist;
       // mlx_put_image_to_window(ray->mlx,ray->mlx_win,ray->screenB,0,0);
    }
    double spriteX = 10-ray->posX;
    double spriteY = 10-ray->posY;
    double invDet = 1.0 / (ray->planeX * ray->dirY - ray->dirX * ray->planeY);
    double transformX = invDet * (ray->dirY * spriteX - ray->dirX * spriteY);
    double transformY = invDet * (-ray->planeY * spriteX + ray->planeX * spriteY);

    int spriteScreenX = (int)((ray->w / 2) * (1 + transformX / transformY));

    int spriteHeight = abs((int)(ray->h / (transformY)));
    int drawStartY = -spriteHeight / 2 + ray->h / 2;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = spriteHeight / 2 + ray->h / 2;
      if(drawEndY >= ray->h) drawEndY = ray->h - 1;

      //calculate width of the sprite
      int spriteWidth = abs( (int) (ray->h / (transformY)));
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= ray->w) drawEndX = ray->w - 1;

      //loop through every vertical stripe of the sprite on screen
      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      {
        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * ray->texture[1].textwidth / spriteWidth) / 256;
        //the conditions in the if are:
        //1) it's in front of camera plane so you don't see things behind you
        //2) it's on the screen (left)
        //3) it's on the screen (right)
        //4) ZBuffer, with perpendicular distance
        if(transformY > 0 && stripe > 0 && stripe < ray->w && transformY < zbuffer[stripe])
        for(int yy = drawStartY; yy < drawEndY; yy++) //for every pixel of the current stripe
        {
          int d = (yy) * 256 - ray->h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
          int texY = ((d * ray->texture[1].textheight) / spriteHeight) / 256;
          int colors = ray->texture[1].imagedata[ray->texture[1].textheight * texY + texX]; //get current color from the texture
          if(colors != -1) ray->imagescreenB[(screenWidth) * yy + stripe] = colors; //paint pixel if it isn't black, black is the invisible color
        }
      }
              mlx_put_image_to_window(ray->mlx,ray->mlx_win,ray->screenB,0,0);
    return (1);
}