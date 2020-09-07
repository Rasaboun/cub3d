#include <mlx.h>
#include <unistd.h>
#include <stdio.h>
#define weight 5
#define height 5 //ADAPTER POUR DRAWVECTORS
#include "math.h"
#define PI 3.14159265359

struct ok{
    void    *mlx;
    void    *mlx_win;
void    *imagepointer;
void    *imagepointer1;
int yy;
int xx;
};

void    drawVector(int xpos,int ypos,int xdir,int ydir,struct ok *YGG)
{
    double xx = xpos;
    double yy = ypos;
    double coef = 1;
    double coeff = 1;
    if (yy > xx) coef = yy/xx;
    if (yy < xx) coeff = xx/yy;
    while (yy < ydir+ypos)
    {

        //mlx_pixel_put(YGG->mlx,YGG->mlx_win,xx,yy,0);
       mlx_put_image_to_window(YGG->mlx,YGG->mlx_win,YGG->imagepointer,xx,yy);
        if(xx <= xdir+xpos)
        {
            xx = xx + coeff;
        }
        yy = yy + coef;
    }
    printf("y = %f, x = %f, coeff = %f, coef  = %f\n",yy,xx,coeff,coef);
}

int colors(int r, int g,int b)
{
    return (b << 24 | g << 16 | r << 8 | 0);
}
int mapX = 16,mapY=8,mapS=64;
int map[]=
{
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,1,1,0,0,0,1,0,0,1,
    1,0,0,0,0,0,0,1,1,0,0,1,0,0,0,1,
    1,0,0,0,0,0,0,1,1,0,1,0,0,0,0,1,
    1,0,0,1,0,0,0,1,1,1,0,0,0,0,0,1,
    1,0,0,1,0,0,0,1,1,0,0,0,0,0,0,1,
    1,0,0,1,0,0,0,1,1,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};

void    drawMap(struct ok *YGG)
{
    int white = 0x9b30ff;
int black = 0x1c1c1c;
int xx,yy,xo,yo;
xo = 0;
yo = 0;
for (yy=0;yy<mapY;yy++)
{
    for(xx=0;xx<mapX;xx++)
    {
        if(map[yy*mapX+xx] == 1){
        mlx_put_image_to_window(YGG->mlx,YGG->mlx_win,YGG->imagepointer,xo,yo);
        }
        else { 
            mlx_put_image_to_window(YGG->mlx,YGG->mlx_win,YGG->imagepointer1,xo,yo);
            }
        xo = xo + weight;
    }
    xo = 0;
    yo = yo + height;
}
}

void    mlx_put_image(void *mlx,void *mlx_win,void *imagepointer){
    int bpp;
    int size_line;
    int endian;
    char    *imagedata = mlx_get_data_addr(imagepointer,&bpp,&size_line,&endian);
    int xpos = 0;
    int ypos = 0;
    while(ypos <= height)
    {
	    while(xpos < weight)
	    {
		int i = xpos*4+4*(size_line/4)*ypos;
		imagedata[i] = (char)0;
		i++;
		imagedata[i] = (char)255;
		i++;
		imagedata[i] = (char)0;
		xpos++;
	    }
	    xpos = 0;
	    ypos++;
    }
}
void drawline(int x0, int y0, int x1, int y1,void*mlx,void*mlx_win)
{
    int dx, dy, p, x, y,temp;
    
    if (y1 < y0)
    {
        temp = y1;
        y1 = y0;
        y0 = temp;
        
    }
	dx=x1-x0;
	dy=y1-y0;
 
	x=x0;
	y=y0;
 
	p=2*dy-dx;
 
	while(x<x1)
	{
		if(p>=0)
		{
			mlx_pixel_put(mlx,mlx_win,x,y,0xeeee);
			y=y+1;
			p=p+2*dy-2*dx;
		}
		else
		{
			mlx_pixel_put(mlx,mlx_win,x,y,0xeeee);
			p=p+2*dy;
		}
		x=x+1;
	}
}

void    ftput(char c)
{
    write(1,&c,1);
}

int deal_key(int key,  void *param)
{

    struct ok *YG = (struct ok*)param;
        mlx_clear_window(YG->mlx,YG->mlx_win);

    if (YG->xx > 0)
        drawVector(200,100,(20 * cos(YG->xx*PI/180)) - (20 * sin(YG->xx*PI/180)),(20 * cos(YG->xx*PI/180)) + (20 * sin(YG->xx*PI/180)),YG);
    if(key == 65363)
        YG->xx = YG->xx + 1;
    if(key == 65364)
        YG->xx = YG->xx + 1;
    if(key == 65361)
    YG->xx = YG->xx + 1;
    if(key == 65362)
    YG->xx = YG->xx - 1;
    return 0;
}
int             main(void)
{
    void    *mlx;
    mlx = mlx_init();
    void    *mlx_win;
    int bpp;
    int size_line;
    int endian;
    int line = 0;
    void    *imagepointer = mlx_new_image(mlx,weight,height);
    void    *imagepointer1 = mlx_new_image(mlx,weight,height);
    char    *imagedata = mlx_get_data_addr(imagepointer,&bpp,&size_line,&endian);
    int key;
    int xpos = 0;
    int ypos = 0;
    while(ypos <= height)
    {
	    while(xpos < weight)
	    {
		int i = xpos*4+4*(size_line/4)*ypos;
		imagedata[i] = (char)255;
		i++;
		imagedata[i] = (char)255;
		i++;
		imagedata[i] = (char)255;
		xpos++;
	    }
	    xpos = 0;
	    ypos++;
    }
    mlx_win = mlx_new_window(mlx, 400, 200, "Hello world!");
   // mlx_put_image_to_window(mlx,mlx_win,imagepointer,200-50,300-50);
    int yy;
    int xx;
    yy = 0;
    xx = 88;
struct ok YGG;

    YGG.imagepointer = imagepointer;
    YGG.imagepointer1 = imagepointer1;
    YGG.mlx = mlx;
    YGG.mlx_win = mlx_win;
    YGG.yy = yy;
    YGG.xx = 0;
   //mlx_put_image(mlx,mlx_win,imagepointer1,weight,height);
    drawline(200,100,220,0,mlx,mlx_win);
    //mlx_put_image_to_window(mlx,mlx_win,imagepointer,0,0);
   // mlx_put_image_to_window(mlx,mlx_win,imagepointer1,0,5);
   drawMap(&YGG);
   //mlx_key_hook(mlx_win,deal_key, &YGG);
    mlx_loop(mlx);
}
