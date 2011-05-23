#ifndef _COMMON_H_
#define _COMMON_H_
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define C_WIDTH 10
#define C_HIGHT 17
#define T___ 0xffffff
#define BORD 0x0
#define X___ 0xffff
#define FONTDATAMAX 4096

typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef unsigned int u32_t;

typedef struct 
{
    int w;
    int h;
    int bpp;
    u8_t *fbmem;
}fb_info, *pinfo_t;

#endif
