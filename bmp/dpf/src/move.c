#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "common.h"
#define N 7

#define DEBUG 0
#if DEBUG
#endif

int move(char *filename,fb_info fb_inf)
{

	fb_info jpeg_inf;

	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

	int i, j, n, m;

	for(i = 0; i < fb_inf.w; i++) {
		for(j = 0; j < fb_inf.h/N; j++)
			for(n = 0; n <= i; n++) 
				fb_pixel(fb_inf, n, j, buf32[j*fb_inf.w + fb_inf.w - i +n]);
	}


	for(j = fb_inf.h/N; j < fb_inf.h; j++)  {
		for(n = fb_inf.h/N; n <= j; n++) 
			for(i = 0; i < fb_inf.w; i++) 
				fb_pixel(fb_inf, i, n, buf32[(fb_inf.h - j + n)*fb_inf.w + i]);
		/*		for(p = 0; p < fb_inf.h/N; p++)
				for(q = 0; q < fb_inf.w; q++)
				fb_pixel(fb_inf, i, j, buf321[j*fb_inf.w + i]);
				*/
		for(m = 0; m < fb_inf.h/N; m++)  
			for(i = 0; i < fb_inf.w; i++) 
				fb_pixel(fb_inf, i, m , buf32[(m + j - fb_inf.h/N +10)*fb_inf.w + i]);

		usleep(10);
	}
	
	free(buf24);
	free(scale_buf);
	free(buf32);

	return 0;
}

