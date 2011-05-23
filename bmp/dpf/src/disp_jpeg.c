
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

int disp_jpeg(char *filename, fb_info fb_inf)
{

	fb_info jpeg_inf;

	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

	//	int i, j, m;
	/*
	   for(i = 0; i < fb_inf.h / 2; --i){
	   for (j = 0; j < fb_inf.w; ++j){
	   m = i + fb_inf.h/2;
	   fb_pixel(fb_inf, j, m, buf32[j + m * fb_inf.w]);
	   }
	   for (j = 0; j < fb_inf.w; ++j){
	   fb_pixel(fb_inf, j, m, buf32[j + m * fb_inf.w]);
	   m = fb_inf.h/2 - i;
	   }
	   usleep(100);
	   }
	   */
	int i, j, m, n, p, q;	
	n = fb_inf.h/2;
	i = fb_inf.w/2, j = fb_inf.w/2, m = fb_inf.h/2, n = fb_inf.h/2;
	while(n > 0) {
		for( q = n; q <= m; q++)
			for( p = i; p <= j;p++ )
				fb_pixel(fb_inf, p, q, buf32[p + q * fb_inf.w]);
		for( q = n; q <= m; q++)
			for( p = i; p <= j;p++ )
				fb_pixel(fb_inf, p, q, buf32[p + q * fb_inf.w]);
		i--; j++; m++; n--;
		usleep(1000);
	}
	while(j < fb_inf.w) {
		for(; j < fb_inf.w; i--, j++){
			for(p = 0; p < fb_inf.h; p++ ) {
				fb_pixel(fb_inf, i, p, buf32[i + p * fb_inf.w]);
				fb_pixel(fb_inf, j, p, buf32[j + p * fb_inf.w]);
			}
				usleep(1000);
		}

	}

	free(buf24);
	free(scale_buf);
	free(buf32);

	return 0;
}
