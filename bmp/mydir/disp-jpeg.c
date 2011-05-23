
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "common.h"

#define DEBUG 0
#if DEBUG
#endif

int display_jpeg(char *filename, fb_info fb_inf)
{

	fb_info original_jpeg;	  /* original size */
	fb_info new_jpeg;

	new_jpeg = fb_inf; 		  /* screen size */
	
	u8_t *buf24 = decode_jpeg(filename, &original_jpeg);
	u8_t * scale_buf = scale24(buf24, new_jpeg, original_jpeg);
	u32_t *buf32 = rgb24to32(scale_buf, new_jpeg);

	int i, j, k;
	for(j = 0; j < new_jpeg.w/2; ++j){
		for (i = 0; i< new_jpeg.h; ++i){
            for (k =0; k<=39; k++) 
            {  
                if(j+39 < new_jpeg.w/2){
                     fb_pixel(fb_inf, new_jpeg.w/2-j-k-1, i, buf32[new_jpeg.w/2-j-40+k+i*new_jpeg.w]);
                     fb_pixel(fb_inf, j+new_jpeg.w/2+k, i, buf32[new_jpeg.w/2+j+39-k+i*new_jpeg.w]);
                     }
                else {
                    if(k < new_jpeg.w/2 - j){
                        fb_pixel(fb_inf, new_jpeg.w/2-j-k-1, i, buf32[k+i*new_jpeg.w]);
                        fb_pixel(fb_inf, new_jpeg.w/2+j+k, i, buf32[new_jpeg.w-1-k+i*new_jpeg.w]);
                    }
                }
            }
			fb_pixel(fb_inf, new_jpeg.w/2-j-1, i, buf32[new_jpeg.w/2-j-1+i*new_jpeg.w]);
            fb_pixel(fb_inf, j+new_jpeg.w/2, i, buf32[j+new_jpeg.w/2+i*new_jpeg.w]);
		}
        usleep(100);
	}

	free(buf24);
	free(scale_buf);
	free(buf32);
	
	return 0;
}
