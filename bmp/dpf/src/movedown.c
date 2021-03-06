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

int movedown(char *filename, fb_info fb_inf)
{

	fb_info jpeg_inf;

	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

	int i, j, n;
	for(j = 0; j < fb_inf.h; j++)  {
		for(n = 0; n <= j; n++) 
			for(i = 0; i < fb_inf.w; i++) 
				fb_pixel(fb_inf, i, fb_inf.h - 1 - j + n, buf32[n*fb_inf.w + i]);
		usleep(10);
	}



	free(buf24);
	free(scale_buf);
	free(buf32);

	return 0;
}
