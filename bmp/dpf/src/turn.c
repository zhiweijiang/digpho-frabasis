
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

int turn(char *filename, fb_info fb_inf)
{

	fb_info jpeg_inf;

	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

	int i, j, w, h, m, n;

	n = 1024;
	m = 1024*5/7;
	while(n > 0) {
	for(j = 0; j < fb_inf.h; j++ )
		for(i = 0; i < fb_inf.w; i++) {
			w = i*n/1024;	
			h = j*m/768;
			fb_pixel(fb_inf, i, j, buf32[h*fb_inf.w + w]);
		}
	n += 7;
	m += 5;
	usleep(10000);
	}
	
	



	free(buf24);
	free(scale_buf);
	free(buf32);

	return 0;
}
