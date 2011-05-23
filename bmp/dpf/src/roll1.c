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

#define DEBUG 0
#if DEBUG
#endif

int roll1(char *filename,char *filename1, fb_info fb_inf)
{

	fb_info jpeg_inf;
	fb_info jpeg_inf1;

	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
	u8_t *buf241 = decode_jpeg(filename1, &jpeg_inf1);
	u8_t * scale_buf1 = scale24(buf241, fb_inf, jpeg_inf1);
	u32_t *buf321 = rgb24to32(scale_buf1, fb_inf);

	int i, j, n, m;
	// x, y is a point of the roll picture
	// w, h is the wide and high of the pictrue
	int x1, y1, w, h;
	w = 325;
	h = 455;
	x1 = 40;
	y1 = 205;

	for(j = 0; j < fb_inf.h; j++)
		for(i = 0; i < fb_inf.w; i++)
			fb_pixel(fb_inf, i, j, buf32[j*fb_inf.w + i]);


	for(j = h - 15; j > 0; j--)  {

		for(n = 0 , m = 15; n <= j; n++, m--) {
			if(m > 0)
				for(i = 0; i < w; i++)  
					fb_pixel(fb_inf, i + x1, y1 + m, buf321[(y1 + h - j + 15 - m - 10)*fb_inf.w + i + x1]);
			for(i = 0; i < w; i++)  {
				//				if(n < h/10&& m > 0)
				//					fb_pixel(fb_inf, i + x1, y1 + n - 15, buf321[(y1 + h - j + n - m+ h/10 - 50 )*fb_inf.w + i + x1]);
				fb_pixel(fb_inf, i + x1, y1 + 15 + n, buf321[(y1 + h - j + n)*fb_inf.w + i + x1]);
			}
		}

		for(n = 0; n < fb_inf.h; n++)
			for(i = 0; i < fb_inf.w; i++)
				if( !(n >= y1 && i >= x1 && n <= y1 + j + 15 && i <= x1 + w) )
					fb_pixel(fb_inf, i, n, buf32[n*fb_inf.w + i]);

		usleep(10000);
	}



	free(buf24);
	free(scale_buf);
	free(buf32);
	free(buf241);
	free(scale_buf1);
	free(buf321);

	return 0;
}
