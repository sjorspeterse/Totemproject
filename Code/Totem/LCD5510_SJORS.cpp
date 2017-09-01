#include "totem.h"

bool LCD5110_SJORS::getPixel(int x, int y)
{
	if ((x>=0) and (x<84) and (y>=0) and (y<48))
	{
		int bi = y % 8;
		int by=((y/8)*84)+x;

		return ((scrbuf[by] & (1<<bi)) > 0);
	}
	return false;
}


/*int8_t LCD5110::getByte(int index)
{
	return (scrbuf[index]);
}*/


void LCD5110_SJORS::getBuffer(int x, int y, uint8_t* bitmap, int sx, int sy)
{
	for(int cy = 0; cy<sy; cy++)
	{
		int bit = cy % 8;
		for(int cx = 0; cx<sx; cx++)
		{
			if(getPixel(x+cx, y+cy)) 
			{
				bitmap[cx + (cy/8)*sx] |= (1<<bit);
			}
			else{
				bitmap[cx + (cy/8)*sx] &= ~(1<<bit);
			}
		}
	}
}

void LCD5110_SJORS::drawBitmapDynamic(int x, int y, uint8_t* bitmap, int sx, int sy)
{
	int bit;
	byte data;

	for (int cy=0; cy<sy; cy++)
	{
		bit= cy % 8;
		for(int cx=0; cx<sx; cx++)
		{
			data=bitmap[(cx+((cy/8)*sx))];
			if ((data & (1<<bit))>0)
				setPixel(x+cx, y+cy);
			else
				clrPixel(x+cx, y+cy);
		}
	}  

}
