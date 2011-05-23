/*
 * jpg文件的特效显示（垂直梳理 打雷 随机雨点 卷轴）
 * 作者：宋彦君
 * 最后修改时间：2010/05/15 13:20
 *
 */
#ifndef __JPGDSP_SYJ__
#define __JPGDSPA_SYJ__

#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h>
#include <math.h>
#include "common.h"

#define RGB(a,b,c) (a<<24|b<<16|c<<8)

#define FB_DEVICE "/dev/fb0"
#define STEP 8 
#define CARD_WIDTH 40

/* 垂直梳理特效 */
extern int jpgdsp_vertical_carding( const char *pfilename, fb_info fbinf );

/* 打雷特效 */
extern int jpgdsp_thunder( const char *pfilename, fb_info fbinf );
/* 随机点特效（带雨点效果） */
extern int jpgdsp_rand_point( const char *pfilename, fb_info fbinf );
/* 卷轴特效 */
extern int jpgdsp_open_scroll( int x, int y, fb_info fbinf );

extern int jpgdsp_movies( const char *pfname, fb_info fbinf );
extern int jpgdsp_door( const char *pfilename, fb_info fbinf  );
#endif

