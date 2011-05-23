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

int moveline1(char *filename, fb_info fb_inf)
{

	fb_info jpeg_inf;

	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

	int i, j, n, m, k;
	for(j = 0; j < fb_inf.w*7/4 ; j++)  {
		m = j;
		for(n = 0, k = 0; n < fb_inf.h; n++, k++)  {
			for(i = 0; i < m; i++)  {
//				if(k >= fb_inf.h) 
//					k = fb_inf.h;		
//				if(i >= fb_inf.w)
//					i = fb_inf.w;
				fb_pixel(fb_inf, i, k, buf32[k*fb_inf.w + i]);
			}
			m--;
		}
	}


	free(buf24);
	free(scale_buf);
	free(buf32);

	return 0;
}
