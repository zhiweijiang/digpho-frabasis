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
        for (j = 300; j < 400; j++) 
        {
            for (i = 0; i < (k+1)*fb_inf.w/16; i++) 
            {
                fb_pixel(fb_inf, i, j, buf32[fb_inf.w-(k+1)*fb_inf.w/16+i+j*fb_inf.w]);
            }
        }
    }

    return 0;
}
