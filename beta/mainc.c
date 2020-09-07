#define mapWidth 13
#define mapHeight 8
#define screenWidth 320
#define screenHeight 200
#define cweight 64
#define cheight 64
#define PI 3.14159265359
#include <stdlib.h>
#include <math.h>
#include <mlx.h>
#include <unistd.h>



int deal_key(int key, void *param);
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
    int *tab;
    int *pertab;
};






int worldMap[mapHeight][mapWidth]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,1,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,1,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1},
};

void    drawMap(struct ok *YGG)
{
    int white = 0x9b30ff;
    int black = 0x1c1c1c;
    int xx,yy,xo,yo;
    xo = 0;
    yo = 0;
for (xx=0;xx<mapHeight;xx++)
{
    for(yy=0;yy<mapWidth;yy++)
    {
        if(worldMap[xx][yy] == 1){
        mlx_put_image_to_window(YGG->mlx,YGG->mlx_win,YGG->imagepointer,xo,yo);
        }
        else { 
        mlx_put_image_to_window(YGG->mlx,YGG->mlx_win,YGG->imagepointer1,xo,yo);
        }
        xo = xo + cweight;
    }
    xo = 0;
    yo = yo + cheight;
}
}
int *line1(int x0, int y0, double x1, double y1,void *mlx,void *mlx_win,int *tab, int color)
{
  double dx = fabs(x1-x0), sx = x0<x1 ? 1 : -1;
  double dy = fabs(y1-y0), sy = y0<y1 ? 1 : -1; 
  double err = (dx>dy ? dx : -dy)/2, e2;
  double x = x0,y = y0;
  while(1){
    mlx_pixel_put(mlx,mlx_win,x0,y0,color);
    if (worldMap[y0/cheight][x0/cweight] == 1){tab[0] = x0 - x;tab[1] = y0 - y;  /*printf("x %d,x0 %f y %d,y0 %f\n dist %f",x0,x,y0,y,(sqrt( pow(y-y0,2) + pow(x-x0,2) )));*/ return tab;} 
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx;}
    if (e2 < dy) { err += dx; y0 += sy;}
  }
}
void line(int x0, int y0, double x1, double y1,void *mlx,void *mlx_win)
{
  double dx = fabs(x1-x0), sx = x0<x1 ? 1 : -1;
  double dy = fabs(y1-y0), sy = y0<y1 ? 1 : -1; 
  double err = (dx>dy ? dx : -dy)/2, e2;
 
  while(1){
    mlx_pixel_put(mlx,mlx_win,x0,y0,0x90ee90);
    if (x0 == x1 && y0 == y1){return;} 
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
}
int main()
{
    void    *mlx;
    void    *mlx_win;
   

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, screenWidth, screenHeight, "Raycasting!");

   int bpp;
    int size_line;
    int endian;
    void    *imagepointer = mlx_new_image(mlx,cweight,cheight);
    void    *imagepointer1 = mlx_new_image(mlx,cweight,cheight);
    char    *imagedata = mlx_get_data_addr(imagepointer,&bpp,&size_line,&endian);
    int key;
    int xpos = 0;
    int ypos = 0;
    float rot;
    double angle;
    double xx,yy,olddir;
    int tab[2];
    int pertab[2];
    while(ypos <= cheight)
    {
	    while(xpos < cweight)
	    {
		int i = xpos*4+4*(size_line/4)*ypos;
		imagedata[i] = (char)0;
		i++;
		imagedata[i] = (char)0;
		i++;
		imagedata[i] = (char)255;
		xpos++;
	    }
	    xpos = 0;
	    ypos++;
    }
    struct ok YGG;
    YGG.mlx = mlx;
    YGG.mlx_win = mlx_win;
    YGG.imagepointer = imagepointer;
    YGG.imagepointer1 = imagepointer1;
    YGG.tab = tab;
    YGG.x = screenWidth/2;
    YGG.y = screenHeight/2 + 50;
    YGG.xx = (double)screenWidth/(double)2;
    YGG.yy = 0.0;
    YGG.rot = 0.0174533*2;
    YGG.pertab = pertab;

    mlx_key_hook(mlx_win,deal_key, &YGG);
    mlx_loop(mlx);
    return 1;
}

int deal_key(int key, void *param)
{
    double old = 0;
    struct ok *YG = (struct ok*)param;
        mlx_clear_window(YG->mlx,YG->mlx_win);
        drawMap(YG);
if(key == 65362)
{
    if (worldMap[(YG->y-10)/cheight][YG->x/cweight] != 1)
        YG->y = YG->y - 10;
    }//haut
if(key == 65364)//bas
{
    if (worldMap[(YG->y+10)/cheight][YG->x/cweight] != 1)
    YG->y = YG->y + 10;
}
if(key == 65363)
{
    if (worldMap[YG->y/cheight][YG->x+10/cweight] != 1)
    YG->x = YG->x + 10;
    }//haut
if(key == 65361)//bas
{
    if (worldMap[YG->y/cheight][(YG->x-10)/cweight] != 1)
    YG->x = YG->x - 10;
}
if(key == 113)//gauche
    {

    old = YG->xx;
    YG->xx = (YG->xx * cos(YG->rot) - YG->yy * sin (YG->rot));
    YG->yy = (old * sin(YG->rot) + YG->yy * cos(YG->rot));  
    }
if(key == 100)//droite
{
    old = YG->xx;
    YG->xx = YG->xx * cos(-YG->rot) - YG->yy * sin (-YG->rot);
    YG->yy = old * sin(-YG->rot) + YG->yy * cos(-YG->rot);  
}
double xx,yy;
    int i = screenWidth/2;
    double dist = 0;
    double root;
    int proj;
    yy = YG->yy;
    xx = YG->xx;
    root = ((double)60/(double)screenWidth) *(PI/(double)180);
    line1(YG->x,YG->y,xx+YG->x,yy+YG->y,YG->mlx,YG->mlx_win,YG->tab,0xcdcdc1);
    dist = sqrt(pow(YG->tab[0],2)+pow(YG->tab[1],2));
    dist = dist * cos(-root);
    //printf("x %i y %d\n",YG->tab[0],YG->tab[1]);
    while(i < screenWidth){
    double rot = ((double)60/(double)screenWidth) *(PI/(double)180);
    old = xx;
    xx = (xx * cos(rot) - yy * sin (rot));
    yy = (old * sin(rot) + yy * cos(rot));   
    line1(YG->x,YG->y,xx+YG->x,yy+YG->y,YG->mlx,YG->mlx_win,YG->tab,0x9b30ff);
    dist = sqrt(pow(YG->tab[0],2)+pow(YG->tab[1],2));
    dist = dist * cos(-root);
    root = root + rot;
    proj = 64/dist * 277;
    line(i, 100-(proj/2),i,proj,YG->mlx,YG->mlx_win);
    i++;
    }
    int y;
    y = screenWidth/2;
    yy = YG->yy;
    xx = YG->xx;
    root = -((double)60/(double)screenWidth) *(PI/(double)180);
   while(y > 0){
    double rot = -((double)60/(double)screenWidth) *(PI/(double)180);
    xx = (xx * cos(rot) - yy * sin (rot));
    yy = (YG->xx * sin(rot) + yy * cos(rot));    
    line1(YG->x,YG->y,xx+YG->x,yy+YG->y,YG->mlx,YG->mlx_win,YG->tab,0x9b30ff);
    dist = sqrt(pow(YG->tab[0],2)+pow(YG->tab[1],2));
   dist = dist * cos(root);
    root = root - rot;
    proj = (64/dist) * 277;
    line(y, 100-(proj/2),y,proj,YG->mlx,YG->mlx_win);
    y--;
    }

    return 1;
}