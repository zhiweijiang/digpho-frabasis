
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
#define N 10

#define DEBUG 0
#if DEBUG
#endif

int rain1(char * filename, fb_info fb_inf)
{

	fb_info jpeg_inf;

	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
	u32_t *buf = malloc(1024*768*4);

	int x, y, x1, y1, x2, y2, i, j;
	srand(time(NULL));
	int m, n;
	m = 0;
	int p, q, rb, rs, w, h;
	rb = 20; 
	rs = 10;
	while(m < 90) {
		n = 0;

		for(j = 0; j < fb_inf.h; j++)
			for(i = 0; i < fb_inf.w; i++)
				fb_pixel(fb_inf, i, j, buf32[j*fb_inf.w + i]);

		while(n < 200)  {
			x1 = rand()%fb_inf.w;
			y1 = rand()%fb_inf.h;
			x2 = x1 + N;
			y2 = y1 + 2*N;
			if(x2 > 0 && x2 < fb_inf.w && y2 < fb_inf.h && y2 > 0)
				myline(x1, y1, x2, y2,0xffffff, fb_inf);

			if(n % 10 == 0) {
			x = rand()%(fb_inf.w - 2*rb) + rb;
			y = rand()%(fb_inf.h - 2*rb) + rb;
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
			}
			n++;
		}
		m++;
	}
	free(buf24);
	free(scale_buf);
	free(buf32);
	return 0;
}
