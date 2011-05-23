
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
#include "common.h"
#include <time.h>

#define DEBUG 0
#if DEBUG
#endif

int zoom3(char *filename, int x, int y, int size, fb_info fb_inf)
{

	fb_info jpeg_inf;

	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
	u32_t *buf = malloc(1024*768*4);

	int i, j, p, q, rb, rs, w, h;

	rs = size*20;
	rb = rs*size; 

	for(j = 0; j < fb_inf.h; j++ )
		for(i = 0; i < fb_inf.w; i++)
			fb_pixel(fb_inf, i, j, buf32[j*fb_inf.w + i]);

	for(j = 0; j < fb_inf.h; j++ )
		for(i = 0; i < fb_inf.w; i++)
			if(i >= x - rs && i <= x + rs && j >= y - rs && j <= y + rs)   {
				w = i - x + rs;
				h = j - y + rs;
				buf[h*2*rs + w] = buf32[j*fb_inf.w + i];
			}

	for(j = 0; j < fb_inf.h; j++ )
		for(i = 0; i < fb_inf.w; i++)
			if(i >= x - rb && i <= x + rb && j >= y - rb && j <= y + rb)   {
				p = i - x + rb;
				q = j - y + rb;
				w = p*rs/rb;
				h = q*rs/rb;
				if(((i - x)*(i - x) + (j - y)*(j - y) <= rb*rb))  {
					fb_pixel(fb_inf, i, j, buf[h*2*rs + w]);
				}
			}


	free(buf24);
	free(scale_buf);
	free(buf32);

	return 0;
}
