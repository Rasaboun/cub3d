#include "raycast.h"
#include "test.h"



void	mini_map(int	*imagescreenB,int screenwidth,int screenheight)
{

	int width;
	int height;
	int ml;
	int mt;
	int i;
	int y;

	y = 0;
	i = 0;

	ml = screenwidth/8;
	mt = screenheight/8;
	width = screenWidth/4;
	height = screenheight/4;

	while (y < height)
	{
	while(i < width)
	{

	imagescreenB[i + ml + screenWidth] = 0xFFFF00;
	i++;


	}
	y++;
	}
}
