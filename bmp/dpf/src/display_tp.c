/*
by yanbin
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "common.h"

#define DEBUG 0
#if DEBUG
#endif


int display_tp(char *filename, fb_info fb_inf)
{
	fb_info jpeg_inf;
	
	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
	int w = 15;
	int h = 10;
	int count = 0;
	srand(time(NULL));
	while (count < fb_inf.w*fb_inf.h-1500)
	{
		int x = rand()%fb_inf.h;
		int y = rand()%fb_inf.w;
		int i, j;
		for (j = x; j < x+h; j++)
		{
			for (i = y; i < y+w; i++)
			{
				if ((0<i && i<fb_inf.w) && (0<j && j<fb_inf.h))
				{
					if (!((int*)fb_inf.fbmem)[j*fb_inf.w + i])
					{
						fb_pixel(fb_inf, i, j, buf32[i + j*fb_inf.w]);
						count++;
					}
				}
			}
		}
	}
	free(buf24);
	free(scale_buf);
	free(buf32);
	return 0;
}

