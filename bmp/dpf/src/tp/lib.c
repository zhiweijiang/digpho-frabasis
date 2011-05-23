#include<stdio.h>
#include<stdlib.h>
#include<sys/mman.h> 
#include<unistd.h>
#include "jpgdsp_syj.h"

#include "common.h"
int hdp(void)
{
	fb_info fb_inf;

	if(init_fb(&fb_inf) < 0) {
		fprintf(stderr, "Error init_fb\n");
		exit(1);
	}

//	char *str = "test.jpg";
//	disp_jpeg("test.jpg", fb_inf);
//	show("test.jpg", fb_inf);
//	shutter("test.jpg", fb_inf);
/*
	if(init_ft(NULL, 128)!= 0)  {
		printf("Error init_ft\n");
		exit(0);
	}
*/
	
#if 0
	door1("taiji.jpg", fb_inf);
	door3("taiji.jpg", fb_inf);
	move("girl1.jpg","girl2.jpg", fb_inf);
	zoom("girl.jpg", fb_inf);
	small("girl2.jpg", fb_inf);
	zoom("girl1.jpg", fb_inf);
	display_string("为人民服务", 300, 400, fb_inf, 0xff0000);
	zoom1("girl1.jpg", fb_inf);
	turn2("girl.jpg" ,"girl1.jpg",fb_inf);
	bang(fb_inf);
	rain("girl1.jpg", fb_inf);

	
	rain1("rever.jpg", fb_inf);
	show("light.jpg", fb_inf);
	bang(fb_inf);
	roll("rever.jpg" ,"story.jpg",fb_inf);

	zoom3("story.jpg", 400, 500, 2, fb_inf);
	snow("rever.jpg", fb_inf);
	
	movetop("rever.jpg", fb_inf);
	movedown("rever.jpg", fb_inf);
	moveconer("rever.jpg", fb_inf);
	moveline("rever.jpg", fb_inf);
	moveline1("rever.jpg", fb_inf);
#endif


	char *filename = "light.jpg";
	char *filename1 = "story.jpg";




#if 1

	show(filename, fb_inf);

	shutter(filename1, fb_inf);
	  
	shutter2(filename, fb_inf);

	door(filename1, fb_inf);

	door1(filename, fb_inf);

	door2(filename1, fb_inf);

	door3(filename, fb_inf);

	door4(filename1, fb_inf);

	movetop("girl.jpg", fb_inf);

	//moveleft(filename, fb_inf);

	move(filename, filename1, fb_inf);


	zoom1(filename, fb_inf);

	//zoom2(filename1, fb_inf);


	small(filename, fb_inf);

	zoom(filename1, fb_inf);
	small1(filename1, fb_inf);

	//turn("girl1.jpg", fb_inf);

	turn2(filename, filename1, fb_inf);

	bang(fb_inf);

	//rain(filename, fb_inf);

	rain1(filename1, fb_inf);

	roll(filename, filename1, fb_inf);

	snow(filename, fb_inf);

	movedown(filename1, fb_inf);

	moveconer(filename, fb_inf);

	moveline(filename1, fb_inf);

	moveline1(filename, fb_inf);

	jpgdsp_open_scroll( 0, 31, fb_inf );

#endif

	return 0;
}
