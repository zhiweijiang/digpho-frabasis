
/*
 *		Copyright (C) 2010	Xu Yinhai (徐银海)<xuyinhai@live.cn>
 *      
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include "common.h"
#define M 40
#define N  1000

#define DEBUG 0
#if DEBUG
#endif

int door2(char *filename, fb_info fb_inf)
{

	fb_info jpeg_inf;

	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

	int point_up_x, point_up_y, point_down_x, point_down_y, point_up_x1, point_up_y1, point_down_x1, point_down_y1 ;
		point_up_x = point_up_x1 = point_down_x = point_down_x1 = fb_inf.w/2;
		point_up_y = point_up_y1 = fb_inf.h/4;
		point_down_y = point_down_y1 = fb_inf.h * 3 / 4;
	int p = fb_inf.h/4 - M/2;
	int i, j, n, m, r;

	srand(time(NULL));

	m = 0;
	while(m < fb_inf.w * 3 /4) {
	for(j = 0; j < fb_inf.h; j++)
		for(i = 0; i < fb_inf.w; i++)	 {
			if(((i - point_up_x)*(i - point_up_x) + (j - point_up_y)*(j - point_up_y) < r * r + N) && 
			   ((i - point_up_x)*(i - point_up_x) + (j - point_up_y)*(j - point_up_y) > r * r - N) &&
				i >= point_up_x)
				fb_pixel(fb_inf, i, j, buf32[j * fb_inf.w + i]);
			if(((i - point_down_x)*(i - point_down_x) + (j - point_down_y)*(j - point_down_y) < r * r + N) && 
			   ((i - point_down_x)*(i - point_down_x) + (j - point_down_y)*(j - point_down_y) > r * r - N) &&
				i <= point_down_x)
				fb_pixel(fb_inf, i, j, buf32[j * fb_inf.w + i]);
			if(((i - point_up_x1)*(i - point_up_x1) + (j - point_up_y1)*(j - point_up_y1) < r * r + N) && 
			   ((i - point_up_x1)*(i - point_up_x1) + (j - point_up_y1)*(j - point_up_y1) > r * r - N) &&
				i >= point_up_x1)
				fb_pixel(fb_inf, i, j, buf32[j * fb_inf.w + i]);
			if(((i - point_down_x1)*(i - point_down_x1) + (j - point_down_y1)*(j - point_down_y1) < r * r + N) && 
			   ((i - point_down_x1)*(i - point_down_x1) + (j - point_down_y1)*(j - point_down_y1) > r * r -N) &&
				i <= point_down_x1)
				fb_pixel(fb_inf, i, j, buf32[j * fb_inf.w + i]);
			r = n + p;
			n = rand()%M;	
		}

	point_up_x++;
	point_down_x++;
	point_up_x1--;
	point_down_x1--;
	m++;
	usleep(10);
	}
	for(j = 0; j < fb_inf.h; j++)
		for(i = 0; i < fb_inf.w; i++)	 
				fb_pixel(fb_inf, i, j, buf32[j * fb_inf.w + i]);

	free(buf24);
	free(scale_buf);
	free(buf32);

	return 0;

	free(buf24);
	free(scale_buf);
	free(buf32);

	return 0;
}
