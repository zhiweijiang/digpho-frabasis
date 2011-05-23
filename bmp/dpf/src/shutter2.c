
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
#define N 20

int shutter2(char *filename, fb_info fb_inf)
{

	fb_info jpeg_inf;

	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

	int i, j, m , n, t, count;

	count = 0;
	t = fb_inf.h/N;
	m = 0; 
	n = 0;
	srand(time(NULL));
	int *sign = malloc(t*4);
	for(i = 0 ; i < t; i++)
		sign[i] = 0;


	while(count < t){	
		for(m = n, j = 0; j < N; m += t, j++)
			for(i = 0; i < fb_inf.w; i++)
				fb_pixel(fb_inf, i, m, buf32[i + m * fb_inf.w]);
		if(!sign[n]) {
			count++;
			sign[n] = 1;
		}
		n = rand()%t;

		usleep(10000);
	}
	free(sign);





	free(buf24);
	free(scale_buf);
	free(buf32);

	return 0;
}
