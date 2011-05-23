
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

#define DEBUG 0
#if DEBUG
#endif

int bang(fb_info fb_inf)
{

/*	fb_info jpeg_inf;

	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
*/
	
	int x, y;
	srand(time(NULL));
	int n = 0;
	while(n < fb_inf.w*fb_inf.h/5)  {
	x = rand()%fb_inf.w;
	y = rand()%fb_inf.h;
	myline(fb_inf.w/2, fb_inf.h/2, x, y,0xffffff, fb_inf);
	n++;
	}





/*	free(buf24);
	free(scale_buf);
	free(buf32);
*/
	return 0;
}
