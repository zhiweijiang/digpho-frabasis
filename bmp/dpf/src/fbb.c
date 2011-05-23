#include<stdio.h>
#include<stdlib.h>
#include<sys/mman.h> 
#include<unistd.h>
#include "jpgdsp_syj.h" 
#include "common.h"
int fbb()
{
	fb_info fb_inf;
	if(init_fb(&fb_inf) < 0) {
		fprintf(stderr, "Error init_fb\n");
		exit(1);
	}
#if 1
	point("../image/1.jpg", fb_inf);
	roll("../image/1.jpg" ,"story.jpg",fb_inf);
	point("../image/2.jpg", fb_inf);
	zoom4("../image/2.jpg", fb_inf);
	moveline("../image/3.jpg", fb_inf);
	move("../image/4.jpg", fb_inf);
	ad("../image/4.jpg", fb_inf);
	display_line("../image/5.jpg",  fb_inf);
	zoom("../image/6.jpg", fb_inf);
	jpgdsp_open_scroll( 30, 30, fb_inf );
	movedown("../image/7.jpg", fb_inf);
	point("../image/8.jpg", fb_inf);
	point("../image/9.jpg", fb_inf);
	point("../image/10.jpg", fb_inf);
	shutter("../image/11.jpg", fb_inf);
	show("../image/12.jpg", fb_inf);
	turn2("../image/12.jpg" ,"../image/13.jpg",fb_inf);
	moveline2("../image/14.jpg", fb_inf);
	shutter2("../image/15.jpg", fb_inf);
	zoom("../image/16.jpg", fb_inf);
	shutter2("../image/17.jpg", fb_inf);
	moveline1("../image/18.jpg", fb_inf);
	point("../image/19.jpg", fb_inf);
	snow("../image/19.jpg", fb_inf);
	door2("../image/20.jpg", fb_inf);
	movetop("../image/21.jpg", fb_inf);
	jpgdsp_rand_point("../image/22.jpg", fb_inf);
	moveline1("../image/23.jpg", fb_inf);
	door3("../image/24.jpg", fb_inf);
	display_shutter("../image/25.jpg", fb_inf);
	turn2("../image/25.jpg", "../image/26.jpg", fb_inf);
	jpgdsp_thunder( "../image/26.jpg",fb_inf );
	rain1("../image/26.jpg", fb_inf);
	jpgdsp_rand_point("../image/27.jpg", fb_inf);
	moveline1("../image/28.jpg", fb_inf);
	small2("../image/28.jpg", "../image/29.jpg", fb_inf);
	shutter("../image/30.jpg", fb_inf);
	small("../image/30.jpg", fb_inf);
	zoom("../image/31.jpg", fb_inf);
	jpgdsp_thunder( "../image/31.jpg",fb_inf );
	jpgdsp_vertical_carding("../image/33.jpg", fb_inf );
	bang(fb_inf);
	point("../image/34.jpg", fb_inf);
	jpgdsp_movies(  "../image/35.jpg",  fb_inf );
	jpgdsp_movies(  "../image/36.jpg",  fb_inf );
	jpgdsp_movies(  "../image/37.jpg",  fb_inf );
	turn2("../image/34.jpg","../image/38.jpg", fb_inf);
	point("../image/39.jpg", fb_inf);
	roll1("../image/39.jpg", "story.jpg", fb_inf);
#endif
	return 0;
}
