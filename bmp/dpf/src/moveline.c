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

int moveline(char *filename, fb_info fb_inf)
{

	fb_info jpeg_inf;

	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

	int i, j, n;
	for(j = 0; j < fb_inf.h; j++)  {
			for(n = 0; n <= j; n++) 
				for(i = j; i > 0; i--) 
					fb_pixel(fb_inf, i, n, buf32[n*fb_inf.w + i]);
		usleep(10000);
	}
	for(; j < fb_inf.w; j++)
		for(n = 0; n < fb_inf.h; n++)
			for(i = 0; i < j; i++)
					fb_pixel(fb_inf, i , n, buf32[n*fb_inf.w + i]);



	free(buf24);
	free(scale_buf);
	free(buf32);

	return 0;
}
