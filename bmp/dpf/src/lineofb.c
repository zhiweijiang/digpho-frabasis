/*
by yanbin
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "common.h"

#define DEBUG 0
#if DEBUG
#endif

int display_line(char *filename, fb_info fb_inf)
{
	fb_info jpeg_inf;
	
	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
	int i, j, count = 0;
#define N 768
	int a[N];
	for (i = 0; i < N; i++) a[i] = 0;
	while (count < fb_inf.h*9/10)
	{
		int y = rand()%fb_inf.h;
		if (!a[y])
		{
			for (j = 0; j < fb_inf.w; j++)
				if ((0<j && j<fb_inf.w) && (0<y && y<fb_inf.h))
					fb_pixel(fb_inf, j, y, buf32[j + y*fb_inf.w]);
			a[y] = 1;
			count++;
		}
		usleep(0.000001);
	}
		for(j = 0; j < fb_inf.h; j++)
			for(i = 0; i< fb_inf.w; i++)
					fb_pixel(fb_inf, i, j, buf32[i + j*fb_inf.w]);

	free(buf24);
	free(scale_buf);
	free(buf32);
	return 0;
}
