#include <stdlib.h>
#include <string.h>
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
    //disp_roller(new_jpeg, buf32);
    //memset(fb_inf.fbmem, 0, fb_inf.w*fb_inf.h*fb_inf.bpp/8);
    //sleep(1);
    //disp_flashed(new_jpeg, buf32);
    //memset(fb_inf.fbmem, 0, fb_inf.w*fb_inf.h*fb_inf.bpp/8);
    //sleep(1);
    //disp_uptodown(new_jpeg, buf32);
    memset(fb_inf.fbmem, 0, fb_inf.w*fb_inf.h*fb_inf.bpp/8);
    disp_cirle(new_jpeg, buf32);
    free(buf24);
	free(scale_buf);
	free(buf32);
	
	return 0;
}
