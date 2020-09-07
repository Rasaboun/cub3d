#include <stdlib.h>
#include <math.h>
 #include <mlx.h>
 #include <unistd.h>
#define PI 3.1415926
#define weight 25
#define height 25


    struct ok{
    void    *mlx;
    void    *mlx_win;
void    *imagepointer;
void    *imagepointer1;
double yy;
double xx;
double rot;
int y;
int x;
};



int mapX = 8,mapY=8,mapS=64;
int map[]=
{
    1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,1,0,0,0,1,
    1,0,0,1,0,0,0,1,
    1,0,0,1,0,0,0,1,
    1,1,1,1,1,1,1,1,
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
            //mlx_pixel_put(YGG->mlx,YGG->mlx_win,xo,yo,0xffaeb9);
        mlx_put_image_to_window(YGG->mlx,YGG->mlx_win,YGG->imagepointer,xo,yo);
        }
        else { 
            //mlx_pixel_put(YGG->mlx,YGG->mlx_win,xo,yo,0);
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
}

//https://www.geeksforgeeks.org/bresenhams-line-generation-algorithm/
//https://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C
void line(int x0, int y0, int x1, int y1,void *mlx,void *mlx_win)
{
  double dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  double dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  double err = (dx>dy ? dx : -dy)/2, e2;
 
  while(1){
    mlx_pixel_put(mlx,mlx_win,x0,y0,0x9b30ff);
    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
}

void line1(int x0, int y0, int x1, int y1,void *mlx,void *mlx_win)
{
  double dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  double dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  double err = (dx>dy ? dx : -dy)/2, e2;
 
  while(1){
    mlx_pixel_put(mlx,mlx_win,x0,y0,0x9b30ff);
    if (map[y0/height*mapX+x0/weight] == 1){return;} 
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
}

int deal_key(int key,  void *param)
{
    struct ok *YG = (struct ok*)param;
        mlx_clear_window(YG->mlx,YG->mlx_win);
        double xxx;
        double yyy;
        double olddir;
        double ollddir;
        int r;
        double xx;
        double yy;
        int dep = 2;
        int *coor;

if(key == 65362)
{
    if(map[(((YG->y - dep)/height))*mapX+(((YG->x)/weight))] != 1)
        YG->y = YG->y - dep;
    }//haut
if(key == 65364)//bas
{
    if(map[(((YG->y + dep)/height))*mapX+(((YG->x)/weight))] != 1)
    YG->y = YG->y + dep;
}
if(key == 65363)
{
    if(map[(((YG->y)/height))*mapX+(((YG->x + dep)/weight))] != 1)
    YG->x = YG->x + dep;
    }//haut
if(key == 65361)//bas
{
    if(map[(((YG->y)/height))*mapX+(((YG->x - dep)/weight))] != 1)
    YG->x = YG->x - dep;
}
    if(key == 113)//gauche
    {

    olddir = YG->xx;
    YG->xx = (YG->xx * cos(-YG->rot) - YG->yy * sin (-YG->rot)) + 1;
    YG->yy = (olddir * sin(-YG->rot) + YG->yy * cos(-YG->rot)) + 1;  
    }
      if(key == 100)//droite
      {
        olddir = YG->xx;
        YG->xx = YG->xx * cos(YG->rot) - YG->yy * sin (YG->rot);
        YG->yy = olddir * sin(YG->rot) + YG->yy * cos(YG->rot);  
      }
    //printf("y = %d x = %d\n",YG->y,YG->x);
    drawMap(YG);
    line1(YG->x,YG->y,YG->xx+YG->x,YG->yy+YG->y,YG->mlx,YG->mlx_win);
    
    yy = YG->yy;
    xx = YG->xx;
       for(r=0;r<320/2;r++)
        {
        double rot = -0.00327249;
        ollddir = xx;
        xx = xx * cos(rot) - yy * sin (rot);
        yy = ollddir * sin(rot) + yy * cos(rot);    
        line1(YG->x,YG->y,xx+YG->x,yy+YG->y,YG->mlx,YG->mlx_win);
  
        r++;
        }
        printf("coor 1 = %f coor 2 = %f ygx %d ygy %d\n",xx+YG->x,yy+YG->y, YG->x,YG->y);
        yy = YG->yy;
    xx = YG->xx;
        for(r=0;r<320/2;r++)
        {
        double rot = 0.00327249;
        ollddir = xx;
        xx = xx * cos(rot) - yy * sin (rot);
        yy = ollddir * sin(rot) + yy * cos(rot);    
        line1(YG->x,YG->y,xx+YG->x,yy+YG->y,YG->mlx,YG->mlx_win);
        //printf("coor 1 = %d coor 2 = %d r = %d\n",coor[0],coor[1],r);
        r++;
        }
        printf("coor 1 = %f coor 2 = %f\n",xx+YG->x,yy+YG->y);
        //line1(YG->x,YG->y,YG->xx+YG->x+50,YG->yy+YG->y,YG->mlx,YG->mlx_win);
    return 0;
}

int main( )
{
    void    *mlx;
    mlx = mlx_init();
    void    *mlx_win;
    int bpp;
    int size_line;
    int endian;
    void    *imagepointer = mlx_new_image(mlx,weight,height);
    void    *imagepointer1 = mlx_new_image(mlx,weight,height);
    char    *imagedata = mlx_get_data_addr(imagepointer1,&bpp,&size_line,&endian);
    int key;
    int xpos = 0;
    int ypos = 0;
    while(ypos <= height)
    {
	    while(xpos < weight)
	    {
		int i = xpos*4+4*(size_line/4)*ypos;
		imagedata[i] = (char)0;
		i++;
		imagedata[i] = (char)0;
		i++;
		imagedata[i] = (char)0;
		xpos++;
	    }
	    xpos = 0;
	    ypos++;
    }
    mlx_win = mlx_new_window(mlx, 320, 200, "Hello world!");
    mlx_put_image(mlx,mlx_win,imagepointer);
  //  mlx_put_image_to_window(mlx,mlx_win,imagepointer,100,100);
    //mlx_put_image_to_window(mlx,mlx_win,imagepointer1,100,100);
    struct ok YGG;
    YGG.xx = 200.0;
    YGG.yy = 0.0;
    YGG.x = 100;
    YGG.y = 100;
    YGG.rot = 0.0174533;
    YGG.mlx = mlx;
    YGG.mlx_win = mlx_win;
    YGG.imagepointer = imagepointer;
    YGG.imagepointer1 = imagepointer1;
    drawMap(&YGG);
    mlx_key_hook(mlx_win,deal_key, &YGG);
    mlx_loop(mlx);
    return 1;
}