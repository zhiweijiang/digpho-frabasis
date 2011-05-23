
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

int show(char *filename, fb_info fb_inf)
{

	fb_info jpeg_inf;

	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

	int i, j, x, y, r;
	r = 0;
	x = fb_inf.w/2;
	y = fb_inf.h/2;
	while(r < 700) {
		for(j = 0; j < fb_inf.h; j++)
			for(i = 0; i < fb_inf.w; i++)
				if((x - i)*(x - i) + (y - j)*(y - j) <= r*r) 
					fb_pixel(fb_inf, i, j, buf32[i + j * fb_inf.w]);
		r++;
//		usleep(100);
	}



	free(buf24);
	free(scale_buf);
	free(buf32);

	return 0;
}
