
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

	int i, j;
	for(i = 0; i < new_jpeg.h; ++i){
		for (j = 0; j < new_jpeg.w; ++j){
			fb_pixel(fb_inf, j, i, buf32[j + i * new_jpeg.w]);
		}
	}

	free(buf24);
	free(scale_buf);
	free(buf32);
	
	return 0;
}
