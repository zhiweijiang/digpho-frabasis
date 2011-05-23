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
#define N 6
#define M 8

#define DEBUG 0
#if DEBUG
#endif

int snow(char * filename, fb_info fb_inf)
{

	fb_info jpeg_inf;

	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

	int x, y, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7, x8, y8, i, j;
	srand(time(NULL));
	int m, n;
	m = 0;
	while(m < 10) {
		n = 0;
		while(n < 50)  {
			x = rand()%(fb_inf.w - 2*N) + N;
			y = rand()%(fb_inf.h - 2*N) + N;
			x1 = x + N; y1 = y;
			x2 = x - N; y2 = y;
			x3 = x;     y3 = y + N;
			x4 = x;		y4 = y - N;
			x5 = x + N; y5 = y + N;
			x6 = x - N; y6 = y + N;
			x7 = x - N; y7 = y - N;
			x8 = x + N; y8 = y - N;
			myline(x1, y1, x, y,0xffffff, fb_inf);
			myline(x2, y2, x, y,0xffffff, fb_inf);
			myline(x3, y3, x, y,0xffffff, fb_inf);
			myline(x4, y4, x, y,0xffffff, fb_inf);
			myline(x5, y5, x, y,0xffffff, fb_inf);
			myline(x6, y6, x, y,0xffffff, fb_inf);
			myline(x7, y7, x, y,0xffffff, fb_inf);
			myline(x8, y8, x, y,0xffffff, fb_inf);

			x = rand()%(fb_inf.w - 2*M) + M;
			y = rand()%(fb_inf.h - 2*M) + M;
			x1 = x + M; y1 = y;
			x2 = x - M; y2 = y;
			x3 = x;     y3 = y + M;
			x4 = x;		y4 = y - M;
			x5 = x + M; y5 = y + M;
			x6 = x - M; y6 = y + M;
			x7 = x - M; y7 = y - M;
			x8 = x + M; y8 = y - M;
			myline(x1, y1, x, y,0xffffff, fb_inf);
			myline(x2, y2, x, y,0xffffff, fb_inf);
			myline(x3, y3, x, y,0xffffff, fb_inf);
			myline(x4, y4, x, y,0xffffff, fb_inf);
			myline(x5, y5, x, y,0xffffff, fb_inf);
			myline(x6, y6, x, y,0xffffff, fb_inf);
			myline(x7, y7, x, y,0xffffff, fb_inf);
			myline(x8, y8, x, y,0xffffff, fb_inf);
			n++;
			usleep(100);
		}
		for(j = 0; j < fb_inf.h; j++)
			for(i = 0; i < fb_inf.w; i++)
				fb_pixel(fb_inf, i, j, buf32[j*fb_inf.w + i]);
		while(n < 50)  {
			x = rand()%(fb_inf.w - 2*N) + N;
			y = rand()%(fb_inf.h - 2*N) + N;
			x1 = x + N; y1 = y;
			x2 = x - N; y2 = y;
			x3 = x;     y3 = y + N;
			x4 = x;		y4 = y - N;
			x5 = x + N; y5 = y + N;
			x6 = x - N; y6 = y + N;
			x7 = x - N; y7 = y - N;
			x8 = x + N; y8 = y - N;
			myline(x1, y1, x, y,0xffffff, fb_inf);
			myline(x2, y2, x, y,0xffffff, fb_inf);
			myline(x3, y3, x, y,0xffffff, fb_inf);
			myline(x4, y4, x, y,0xffffff, fb_inf);
			myline(x5, y5, x, y,0xffffff, fb_inf);
			myline(x6, y6, x, y,0xffffff, fb_inf);
			myline(x7, y7, x, y,0xffffff, fb_inf);
			myline(x8, y8, x, y,0xffffff, fb_inf);

			x = rand()%(fb_inf.w - 2*M) + M;
			y = rand()%(fb_inf.h - 2*M) + M;
			x1 = x + M; y1 = y;
			x2 = x - M; y2 = y;
			x3 = x;     y3 = y + M;
			x4 = x;		y4 = y - M;
			x5 = x + M; y5 = y + M;
			x6 = x - M; y6 = y + M;
			x7 = x - M; y7 = y - M;
			x8 = x + M; y8 = y - M;
			myline(x1, y1, x, y,0xffffff, fb_inf);
			myline(x2, y2, x, y,0xffffff, fb_inf);
			myline(x3, y3, x, y,0xffffff, fb_inf);
			myline(x4, y4, x, y,0xffffff, fb_inf);
			myline(x5, y5, x, y,0xffffff, fb_inf);
			myline(x6, y6, x, y,0xffffff, fb_inf);
			myline(x7, y7, x, y,0xffffff, fb_inf);
			myline(x8, y8, x, y,0xffffff, fb_inf);
			n++;
			usleep(100);
		}
		for(j = 0; j < fb_inf.h; j++)
			for(i = 0; i < fb_inf.w; i++)
				fb_pixel(fb_inf, i, j, buf32[j*fb_inf.w + i]);
		usleep(100);
		m++;

	}
	free(buf24);
	free(scale_buf);
	free(buf32);
	return 0;
}
