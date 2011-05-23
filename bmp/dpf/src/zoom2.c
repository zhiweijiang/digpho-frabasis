
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

int zoom2(char *filename, fb_info fb_inf)
{

	fb_info jpeg_inf;

	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
	u32_t *buf = malloc(1024*768*4);

	srand(time(NULL));

	int i, j, p, q, x, y, rb, rs, w, h;
	rb = 120; 
	rs = 60;

	for(j = 0; j < fb_inf.h; j++ )
		for(i = 0; i < fb_inf.w; i++)
			fb_pixel(fb_inf, i, j, buf32[j*fb_inf.w + i]);

	// restore the place need to zoom
	/*
	   for(j = 0; j < fb_inf.h; j++ )
	   for(i = 0; i < fb_inf.w; i++)
	   if(((i - x)*(i - x) + (j - y)*(j - y) < rs*rs))   {
	   w = i - x + rs;
	   h = j - y + rs;
	   buf[h*2*rs + w] = buf32[j*fb_inf.w + i];
	   }
	   */	
	int n = 0;
	while(n < 50) {
		if( n < 0) {
		x = rand()%(fb_inf.w - 2*rb) + rb;
		y = rand()%(fb_inf.h - 2*rb) + rb;
		usleep(1000000);
		}
		else  {
			x = rb;
			y = x * x;
			usleep(100000);
		}

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

	for(j = 0; j < fb_inf.h; j++ )
		for(i = 0; i < fb_inf.w; i++)
			fb_pixel(fb_inf, i, j, buf32[j*fb_inf.w + i]);
	n++;
	}



	free(buf24);
	free(scale_buf);
	free(buf32);

	return 0;
}
