#include <stdio.h>
#include <errno.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>

#include "common.h"

#define FB_DEVICE "/dev/fb0"

int init_fb(fb_info *fb_inf)
{
	int fd;

	if ((fd = open(FB_DEVICE, O_RDWR)) < 0){
		fprintf(stderr, "Open %s failed:%s\n", FB_DEVICE, strerror(errno));
		return -1;
	}

	struct fb_var_screeninfo fb_var;
	
	if (ioctl(fd, FBIOGET_VSCREENINFO, &fb_var) < 0){
		fprintf(stderr, "fb ioctl failed:%s\n", strerror(errno));
		return -1;
	}

#if 1	
	fb_inf->w = fb_var.xres;
	fb_inf->h = fb_var.yres;
	fb_inf->bpp = fb_var.bits_per_pixel;
#else
	fb_inf->w = 1280;
	fb_inf->h = 800;
	fb_inf->bpp = fb_var.bits_per_pixel;

#endif



#if 1
	printf("width:%d\thign:%d\tbpp:%d\n",
		  fb_inf->w, fb_inf->h, fb_inf->bpp);
#endif	
	fb_inf->fbmem = mmap(0, fb_inf->w * fb_inf->h * fb_inf->bpp /8,
					 PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (fb_inf->fbmem == MAP_FAILED){
		fprintf(stderr, "fb mmap failed:%s\n", strerror(errno));
		return -1;
	}
	
	close(fd);
	
	return 0;
}

int fb_pixel(fb_info fb_inf, int x, int y, u32_t color)
{
	u8_t *pos = (u8_t*)fb_inf.fbmem + (fb_inf.w * y + x) * fb_inf.bpp/8;

	switch (fb_inf.bpp){
	case 32:				  /* 32 bits */
		*(pos + 3) = color >> 24;
	case 24:				  /* 24 bits */
		*(pos + 2) = color >> 16;
	case 16:	  		       /* 16 bits */
		*(pos + 1) = color >> 8;
	case 8:			      /* 8 bits */
		*pos = color;
		return 0;
	default:
		return -1;
	}

	return -1;
}


/* painting horizontal */
int fb_pixel_row(fb_info fb_inf, int x, int y, int len, u32_t color)
{
	int i;
#if 1
	for(i = x; i < len; i++){
		fb_pixel(fb_inf,x+i, y, color);
	}
#else
	/* FIXME: not */
//	memset(fb_inf.fbmem + (y * fb_inf.w + x) * fb_inf.bpp/8, color, len * 
#endif

	return 0;
}

int  swap(int *a, int *b)
{
    int *tmp = NULL;

    *a = *tmp;
    *a = *b;
    *b = *tmp;

    return 0;
}

int fb_line(fb_info fb_inf, int x1, int y1, int x2, int y2, u32_t color)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int p = 0;
    int inc = (dx * dy < 0) ? -1 : 1;

    if (abs(dx) > abs(dy)) 
    {
        if (dx < 0) 
        {
            swap(&x1, &x2);
            swap(&y1, &y2);
            dx = -dx;
            dy = -dy;
        }
        
        dy = abs(dy);
        p = 2 * dy -dx;

        while (x1 <= x2) 
        {
            fb_pixel(fb_inf, x1, y1, color);
            x1++;
            if (p < 0) 
            {
                p += 2 * dy;
            }
            else 
            {
                y1 += inc;
                p += 2 * (dy - dx);
            }
        }
    }
    else 
    {
        if (dy < 0) 
        {
            swap(&x1, &x2);
            swap(&y1, &y2);
            dx = -dx;
            dy = -dy;
        }
        
        dx = abs(dx);
        p = 2 * dx - dy;

        while (y1 <= y2) 
        {
            fb_pixel(fb_inf, x1, y1, color);
            y1++;
            if (p < 0) 
            {
                p += 2 * dx;
            }
            else 
            {
                x1 += inc;
                p += 2 * (dx - dy);
            }
        }
    }
    return 0;
}

int fb_left_half_cirle(fb_info fb_inf, int x0, int y0, int r, u32_t color)
{ int x = 0;
    int y = r;
    int p = 3 - 2*r;
    
    while(y >= x)
    {
      //  fb_pixel(fb_inf, x0+x, y0+y, color);
      //  fb_pixel(fb_inf, x0+y, y0+x, color);
        fb_pixel(fb_inf, x0-x, y0+y, color); 
      //  fb_pixel(fb_inf, x0+x, y0-y, color);
        fb_pixel(fb_inf, x0-y, y0+x, color);
        fb_pixel(fb_inf, x0-x, y0-y, color);
      //  fb_pixel(fb_inf, x0+y, y0-x, color);
       fb_pixel(fb_inf, x0-y, y0-x, color);
        if(p >= 0)
        {
            y --;
            p += (4*(x-y) + 10); 
        }
        else
        {
            p += (4*x + 6);
        }
        x++;
    }
    
    return 0;
}

int fb_cirle(fb_info fb_inf, int x0, int y0, int r, u32_t color)
{ int x = 0;
    int y = r;
    int p = 3 - 2*r;
    
    while(y >= x)
    {
        fb_pixel(fb_inf, x0+x, y0+y, color);
        fb_pixel(fb_inf, x0+y, y0+x, color);
        fb_pixel(fb_inf, x0-x, y0+y, color); 
        fb_pixel(fb_inf, x0+x, y0-y, color);
        fb_pixel(fb_inf, x0-y, y0+x, color);
        fb_pixel(fb_inf, x0-x, y0-y, color);
        fb_pixel(fb_inf, x0+y, y0-x, color);
        fb_pixel(fb_inf, x0-y, y0-x, color);
        if(p >= 0)
        {
            y --;
            p += (4*(x-y) + 10); 
        }
        else
        {
            p += (4*x + 6);
        }
        x++;
    }
    
    return 0;
}

int fb_test(void)
{

	printf("Framebuffer Test\n");
	
	fb_info fb_inf;
	if(init_fb(&fb_inf) < 0)
		return -1;
	printf("Framebuffer  Test fb_pixel\n");
	
	/* point test */
//	point_t p, p2; p.x = 640;	p.y = 400;
	fb_pixel(fb_inf, 640, 400, 0xFFFFFFFF);

	/* line test*/
//	p.x = 0; p.y = 200;
//	p2.x = 1280, p2.y = 200;
	fb_pixel_row(fb_inf, 0, 200, 1280, 0xFF0000);
	

	munmap(fb_inf.fbmem, fb_inf.w * fb_inf.h * fb_inf.bpp / 8);
	return 0;
}

