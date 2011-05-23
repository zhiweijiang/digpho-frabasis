#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "common.h"


int font_char(pinfo_t fb,int x,int y, int src, u32_t color);
int font_str(pinfo_t fb, int x, int y, char *str, u32_t color);
int init_fb(pinfo_t fb);
int fb_pixel(pinfo_t fb, int x, int y, u32_t color);


extern  const unsigned char fontdata_8x16[FONTDATAMAX];

int main(int argc, const char *argv[])
{
    fb_info fb;
    char str[100] =" You are world !";

    if(init_fb(&fb) < 0)
    {
        perror("init_fb");
        exit(1);
    }
    
    font_str(&fb, 500, 400, str, 0xff00); 

    return 0;
}

int init_fb(pinfo_t fb)
{
    int fd;

    if((fd = open("/dev/fb0", O_RDWR)) < 0)
    {
        perror("fb0");
        return -1;
    }

    struct fb_var_screeninfo fb_var;

    if((ioctl(fd, FBIOGET_VSCREENINFO, &fb_var) < 0))
    {
        perror("ioctl");
        return -1;
    }
    fb->w = fb_var.xres;
    fb->h = fb_var.yres;
    fb->bpp = fb_var.bits_per_pixel;
    printf("w:%d\th:%d\tbpp:%d\n", fb->w, fb->h, fb->bpp);

    fb->fbmem = mmap(NULL, ((fb->w)*(fb->h)*(fb->bpp)/8), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(fb->fbmem == MAP_FAILED)
    {
        perror("mmap");
        return -1;
    }

    close(fd);
    memset(fb->fbmem, 0, (fb->w)*(fb->h)*(fb->bpp)/8);
    return 0;
}

int fb_pixel(pinfo_t fb, int x, int y, u32_t color)
{
    u32_t *p;

    p = (u32_t *) ((char *)fb->fbmem +((fb->w*y+x)*fb->bpp)/8);
    *p = color;

    return 0;
}

int font_str(pinfo_t fb, int x, int y, char *str, u32_t color)
{
    int i = 0;
    
    while(*str != '\0')
    {   
        font_char(fb, x+8*i, y, (int)(*str), color);
        str ++;
        i++;
    }
    
    return 0;
}

int font_char(pinfo_t fb, int x, int y, int src, u32_t color)
{
    int i, j;
    unsigned char mask = 0x01;

    for (i = 0; i < 16; i++) 
    {
        for (j = 7; j >= 0; j--) 
        {
            if( (fontdata_8x16[src*16+i] & (mask << j)))
                fb_pixel(fb, x-j, y +i, color);
        }
        usleep(1000);
    }

    return 0;
}
