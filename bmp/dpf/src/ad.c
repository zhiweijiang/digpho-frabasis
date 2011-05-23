/*
 * Yan Bin
 * */	

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "common.h"

#define DEBUG 0
#if DEBUG
#endif

int ad(char *filename, fb_info fb_inf)
{

	fb_info jpeg_inf;

	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

	if (init_ft("x.ttf", 64) != 0){
		fprintf(stderr, "Error initial font\n")	;
		return 1;
	}


	int i , j, x, k, m, y;
	x = fb_inf.w-450;
	for(j =  0 ; j < fb_inf.h; j++)
		for(i = 0 ; i < fb_inf.w; i++)
			fb_pixel(fb_inf, i , j, buf32[j * fb_inf.w +i  ]);
	for (m  = 0; m < 2; m++)
	{
		for (k = 0; k < fb_inf.w; k+=200)
		{
			if (0<=x-k && x-k<fb_inf.w)
				display_string("同彬牌生发灵,居家必备之良药.", x-k, fb_inf.h-10, fb_inf, 0x00ff00);
			sleep(1);
			for (j = fb_inf.h; j > fb_inf.h-70; j--)
				for (i = 0; i < fb_inf.w; i++)
					if (0<=i && i<fb_inf.w && 0<=j && j<fb_inf.h)
						fb_pixel(fb_inf, i, j, buf32[i + j * fb_inf.w]);
		}
		x = fb_inf.w-450;
		y = fb_inf.h/2;
		for (k = 0; k < fb_inf.w; k+=200)
		{
			if (0<=x-k && x-k<fb_inf.w)
				display_string("本项目由亚嵌教育独家赞助", x-k, y-30, fb_inf, 0xff0000);
			sleep(1);
			for (j = y-10; j > y-90; j--)
				for (i = 0; i < fb_inf.w; i++)
					if (0<=i && i<fb_inf.w && 0<=j && j<fb_inf.h)
						fb_pixel(fb_inf, i, j, buf32[i + j * fb_inf.w]);
		}
		x = fb_inf.w-400;
		for (k = 0; k < fb_inf.w; k+=200)
		{
			if (0<=x-k && x-k<fb_inf.w)
				display_string("吴老师减肥茶,喝了就知道!", x-k, 90, fb_inf, 0x00ffff);
			sleep(1);
			for (j = 0; j < 100; j++)
				for (i = 0; i < fb_inf.w; i++)
					if (0<=i && i<fb_inf.w && 0<=j && j<fb_inf.h)
						fb_pixel(fb_inf, i, j, buf32[i + j * fb_inf.w]);
		}
	}

	free(buf24);
	free(scale_buf);
	free(buf32);

	return 0;
}
