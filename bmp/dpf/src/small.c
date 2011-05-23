
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

int small(char *filename, fb_info fb_inf)
{

	fb_info jpeg_inf;

	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

	int i, j, w, h, p, q, n;


	int	newh ,neww;
	
	n = 0;
	while(n<768) {
	newh = fb_inf.h - n;
	neww = fb_inf.w - n * fb_inf.w/fb_inf.h;
	p = (fb_inf.h - newh)/2;
	q = (fb_inf.w - neww)/2;
	for(j = 0; j < newh; j++)
		for(i = 0; i < neww; i++) {
			w = fb_inf.w * i/neww; 
			h = fb_inf.h * j/newh;
			fb_pixel(fb_inf, i + q, j + p, buf32[h*fb_inf.w + w]);
		}
	n++;
	}
			



	free(buf24);
	free(scale_buf);
	free(buf32);

	return 0;
}
