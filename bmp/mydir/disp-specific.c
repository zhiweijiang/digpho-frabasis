#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "common.h"

int disp_roller(fb_info fb_inf, u32_t *buf32)
{
    int i, j, k;

    for(j = 0; j < fb_inf.w/2; ++j)
    {
        for (i = 0; i< fb_inf.h; ++i)
        {
            for (k =0; k<=39; k++) 
            {  
                if(j+39 < fb_inf.w/2)
                {
                    fb_pixel(fb_inf, fb_inf.w/2-j-k-1, i, 
                            buf32[fb_inf.w/2-j-40+k+i*fb_inf.w]);

                    fb_pixel(fb_inf, j+fb_inf.w/2+k, i, 
                            buf32[fb_inf.w/2+j+39-k+i*fb_inf.w]);
                }
                else 
                {
                    if(k < fb_inf.w/2 - j)
                    {
                        fb_pixel(fb_inf, fb_inf.w/2-j-k-1, i, 
                                buf32[k+i*fb_inf.w]);

                        fb_pixel(fb_inf, fb_inf.w/2+j+k, i, 
                                buf32[fb_inf.w-1-k+i*fb_inf.w]);
                    }
                }
            }
            fb_pixel(fb_inf, fb_inf.w/2-j-1, i, 
                    buf32[fb_inf.w/2-j-1+i*fb_inf.w]);
            fb_pixel(fb_inf, j+fb_inf.w/2, i, 
                    buf32[j+fb_inf.w/2+i*fb_inf.w]);
        }
        usleep(100);
    }

    return 0;
}

int disp_flashed(fb_info fb_inf, u32_t *buf32)
{
    int i, j, k;
        
    for(k = 0; k < 16; k++) 
    {
        for (j = 0; j < fb_inf.h; j++) 
        {
            for (i = 0; i < (k+1)*fb_inf.w/16; i++) 
            {
                fb_pixel(fb_inf, i, j, buf32[fb_inf.w-(k+1)*fb_inf.w/16+i+j*fb_inf.w]);
            }
        }
    }

    return 0;
}

int disp_uptodown(fb_info fb_inf, u32_t *buf32)
{
    int i, j, k;
        
    for(k = 0; k < 16; k++) 
    {
        for (j = 0; j < (k+1)*fb_inf.h/16; j++) 
        {
            for (i = 0; i < (k+1)*fb_inf.w/16; i++) 
            {
                fb_pixel(fb_inf, i, j,  buf32[fb_inf.w-(k+1)*fb_inf.w/16+i+(fb_inf.h-(k+1)*fb_inf.h/16+j)*fb_inf.w]);
            }
        } 
        usleep(100);
    }

    return 0;
}


int disp_cirle(fb_info fb_inf, u32_t *buf32)
{
    int x0 = 0;
    int y0 = fb_inf.h/2;
    int x, y, p;
    int i = 0, j, k;
       for (x0 = 1; x0 < fb_inf.w - fb_inf.h/2; ++x0) 
        {
            if(i < fb_inf.h/2)
                i++;

            y = i;
            p = 3 - 2*i;
            x= 0;
            if(x0 < fb_inf.h/2+1)
            {
                 while(y >= x)
                {
                    for (k = 0; k < 3; k++) 
                    {
                        fb_pixel(fb_inf, x0+x+k, y0-y, buf32[x0+x+k+(y0-y)*fb_inf.w]);
                        fb_pixel(fb_inf, x0+y+k, y0-x, buf32[x0+y+k+(y0-x)*fb_inf.w]);
                        fb_pixel(fb_inf, x0+x+k, y0+y, buf32[x0+x+k+(y0+y)*fb_inf.w]);
                        fb_pixel(fb_inf, x0+y+k, y0+x, buf32[x0+y+k+(y0+x)*fb_inf.w]);
                        fb_pixel(fb_inf, x0-x+k, y0-y, buf32[x0-x+k+(y0-y)*fb_inf.w]);
                        fb_pixel(fb_inf, x0-y+k, y0-x, buf32[x0-y+k+(y0-x)*fb_inf.w]);
                        fb_pixel(fb_inf, x0-x+k, y0+y, buf32[x0-x+k+(y0+y)*fb_inf.w]);
                        fb_pixel(fb_inf, x0-y+k, y0+x, buf32[x0-y+k+(y0+x)*fb_inf.w]);
                    }

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
                 if(i%10 == 9)
                  usleep(5000);
            }
            else
            {
                fb_left_half_cirle(fb_inf, x0-1, y0, i, 0x00);
                while(y >= x)
                {
                    fb_pixel(fb_inf, x0+x, y0-y, buf32[x0+x+(y0-y)*fb_inf.w]);
                    fb_pixel(fb_inf, x0+y, y0-x, buf32[x0+y+(y0-x)*fb_inf.w]);
                    fb_pixel(fb_inf, x0+x, y0+y, buf32[x0+x+(y0+y)*fb_inf.w]);
                    fb_pixel(fb_inf, x0+y, y0+x, buf32[x0+y+(y0+x)*fb_inf.w]);

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
                if(x0%10 == 9)
                    usleep(5000);

            }      
            if(x0 == fb_inf.w - fb_inf.h/2 - 1)
            {
                for(j = i; j >= 0; j--)
                {
                    for (k = 0; k < 3; k++) 
                    {
                        fb_cirle(fb_inf, x0-k, y0, j, 0x00);
                    }  
                    if(x0%10 == 9)
                        usleep(1000);
                    x0++;
                }

            }

        }
        return 0;
    }


