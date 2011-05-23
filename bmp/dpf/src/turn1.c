
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

int turn1(char *filename, fb_info fb_inf)
{

	fb_info jpeg_inf;
	//	fb_info jpeg_inf1;

	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	//	u8_t *buf241 = decode_jpeg(filename1, &jpeg_inf1);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	//	u8_t * scale_buf1 = scale24(buf241, fb_inf, jpeg_inf1);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
	//	u32_t *buf321 = rgb24to32(scale_buf1, fb_inf);


	/*		for(j = 0; j < (fb_inf.h - newh)/2 || j > newh + (fb_inf.h - newh)/2; j++)
			for(i = 0;  i < fb_inf.w; i++ )
			if(i > neww)
			fb_pixel(fb_inf, i, j, buf321[j*fb_inf.w + i]);
			*/
	int i, j, h, w, new_h, new_w, n;
	new_h = fb_inf.h;
	n = 0;
//	while(new_h) {
		for(j = fb_inf.h - new_h; j < fb_inf.h; j++) {
			new_w = fb_inf.w -j + j*(n++)/fb_inf.h;
			for(i = (fb_inf.w - new_w)/2; i < fb_inf.w - (fb_inf.w - new_w)/2; i++) {
				w = i*fb_inf.w/new_w;
				h = j*fb_inf.h/new_h;
				fb_pixel(fb_inf, i, j, buf32[h*fb_inf.w + w]);
			}
		}
//		new_h -= 10;
//		usleep(1000);
//	}



	free(buf24);
	free(scale_buf);
	free(buf32);

	return 0;
}
