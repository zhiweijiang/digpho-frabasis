
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

int turn3(char *filename,  fb_info fb_inf)
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
	int i, j, h, w, new_h, new_w, m, n;
	new_h = fb_inf.h;
	n = m = 0;
	while(new_h>0) {
		for(j = 0; j < new_h; j++) {
			new_w = fb_inf.w -m + m*(n++)/new_h;
			h = j*fb_inf.h/new_h;
			for(i = 0; i < new_w; i++) {
				w = i*fb_inf.w/new_w;
				if(i + (fb_inf.w - new_w)/2 > 0 && i + (fb_inf.w - new_w)/2 < fb_inf.w && j + fb_inf.h - new_h > 0&& j + fb_inf.h - new_h < fb_inf.h)
				fb_pixel(fb_inf, i + (fb_inf.w - new_w)/2, j + fb_inf.h - new_h, buf32[h*fb_inf.w + w]);
			}
		}
		m += 1;
		n = 0;
		new_h -= 5;
		usleep(1000);
	}



	free(buf24);
	free(scale_buf);
	free(buf32);

	return 0;
}
