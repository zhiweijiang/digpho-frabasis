/*
 *		Copyright (C) 2010	Xu Yinhai (徐银海)<xuyinhai@live.cn>
 *      
 */
#ifndef __COMMON_H__
#define __COMMON_H__
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <time.h>
#include <string.h>
#include <linux/fb.h>

//#include "mouse.h"

typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef unsigned int u32_t;

typedef struct 
{
	int w;				  /* width */
	int h;				  /* high */
	int bpp;				  /* bits per pixel */
	u8_t *fbmem;
}fb_info;

/* ******************** fb.c ******************** */

/* initial framebuf */
extern int init_fb(fb_info *fb_inf);

/* drawing pixel */
extern int fb_pixel(fb_info fb_inf, int x, int y, u32_t color);

/* Framebuffer Test */
int fb_test(void);


/* ******************** jpeg.c ******************** */

/*This returns an array for a 24 bit image.*/
extern u8_t *decode_jpeg (const char *filename, fb_info *jpeg_inf);

extern u32_t * rgb24to32(u8_t *buf24, fb_info jpeg_inf);
extern u16_t * rgb24to16(u8_t *buf24, fb_info jpeg_inf);

extern u8_t * scale24(u8_t *buf24, fb_info new_inf, fb_info jpeg_inf);


/* ******************** disp_jpeg.c ******************** */
/* display jpeg */
extern int disp_jpeg(char *filename, fb_info fb_inf);


/* ******************** font.c ******************** */
extern int init_ft (const char *file, int size);
extern int display_string (const char *buf, int x, int y, fb_info fb_inf,u32_t color);


/* ******************** mouse.c ******************** */
extern int test_mouse(fb_info fb_inf);

/* ******************** disp-basic.c ******************** */
/* create jpeg middle data file */
extern int create_jpeg(const char *filejpeg, const char *newfile, fb_info fb_inf);
/* use middle data file to display */
extern int basic_disp(const char * filename, fb_info fb_inf);

extern int show(char *filename, fb_info fb_inf);

extern int shutter(char *filename, fb_info fb_inf);
  
extern int shutter2(char *filename, fb_info fb_inf);

extern int door(char *filename, fb_info fb_inf);

extern int door1(char *filename, fb_info fb_inf);

extern int door2(char *filename, fb_info fb_inf);

extern int door3(char *filename, fb_info fb_inf);

extern int door4(char *filename, char *filename1, fb_info fb_inf);

extern int movetop(char *filename, fb_info fb_inf);

extern int moveleft(char *filename, fb_info fb_inf);

extern int move(char *filename, fb_info fb_inf);

extern int zoom(char *filename, fb_info fb_inf);

extern int zoom1(char *filename, fb_info fb_inf);

extern int zoom2(char *filename, fb_info fb_inf);

extern int zoom3(char *filename, int x, int y, int size, fb_info fb_inf);

extern int zoom4(char *filename, fb_info fb_inf);

extern int small(char *filename, fb_info fb_inf);

extern int small1(char *filename, fb_info fb_inf);

extern int turn(char *filename, fb_info fb_inf);

extern int turn2(char *filename, char *filename1, fb_info fb_inf);

extern int myline(int x1,int y1,int x2,int y2,int color, fb_info fb_inf);

extern int bang(fb_info fb_inf);

extern int rain(char *filename, fb_info fb_inf);

extern int rain1(char *filename, fb_info fb_inf);

extern int roll(char *filename, char *filename1, fb_info fb_inf);

extern int roll1(char *filename, char *filename1, fb_info fb_inf);

extern int snow(char *filename, fb_info fb_inf);

extern int movedown(char *filename, fb_info fb_inf);

extern int moveconer(char *filename, fb_info fb_inf);

extern int moveline(char *filename, fb_info fb_inf);

extern int moveline1(char *filename, fb_info fb_inf);

extern int moveline2(char *filename, fb_info fb_inf);

extern int hdp(void);

extern int display_tp(char *filename, fb_info fb_inf);

extern int display_line(char *filename, fb_info fb_inf);

extern int point(char *filename, fb_info fb_inf);

extern int point1(char *filename, fb_info fb_inf);

extern int display_jpeg(char *filename, fb_info fb_inf);

extern int button_click(fb_info fb_inf);

extern int display_shutter(char *filename, fb_info fb_inf);

extern int small2(char *filename, char *filename1, fb_info fb_inf);

extern int jpgdsp_door( const char *pfilename, fb_info fbinf  );

extern int ad(char *filename, fb_info fb_inf);

extern int fbb();




#endif
