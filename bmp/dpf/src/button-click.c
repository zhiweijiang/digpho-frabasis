/* ********** .h */
#include "common.h"
#include "mouse.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <time.h>
#include <string.h>
#include <linux/fb.h>

typedef struct {
	int x;
	int y;
}ico;

int button_click(fb_info fb_inf)
{
	int mfd;
	mouse_open(NULL, &mfd);
	/* highlight ico */
	fb_info jpeg_inf;
	fb_info b_inf;
	if (init_fb(&b_inf) < 0)
	{
		printf("Error init_fb\n");
		exit(1);
	}
	u8_t *buf24 = decode_jpeg("mainframel.jpg", &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, b_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, b_inf);

	/* initialize font */
	if (init_ft("x.ttf", 45) != 0){
		fprintf(stderr, "Error initial font\n")	;
		return 1;
	}



	int m_x = fb_inf.w / 2;
	int m_y = fb_inf.h / 2;
	fb_drawcursor(fb_inf, m_x, m_y);

	u8_t buf[8];
	mouse_event_t mevent;
	 
	ico fkey[9];
	fkey[0].x = 34;
	fkey[0].y = 34;
	fkey[1].x = 34;
	fkey[1].y = 178;
	fkey[2].x = 34;
	fkey[2].y = 322;
	fkey[3].x = 34;
	fkey[3].y = 510;
	fkey[4].x = 34;
	fkey[4].y = 660;
	fkey[5].x = 262;
	fkey[5].y = 46;
	fkey[6].x = 265;
	fkey[6].y = 180;
	fkey[7].x = 469;
	fkey[7].y = 46;
	fkey[8].x = 823;
	fkey[8].y = 595;
	char *discription[9] = {"图片", "音乐", "电子书",
		"设置", "时间", "幻灯", "浏览", "关于", "退出"};
	int door2 = 1;

	/* loading ... */
	display_jpeg("loading.jpg", fb_inf);
	display_string("loading", 200, 450, fb_inf, 0x00ff55e3);
	/* initialize font */
	if (init_ft("x.ttf", 84) != 0){
		fprintf(stderr, "Error initial font\n")	;
		return 1;
	}
	int c = 3; /* loading time */	
	while (c)
	{
		int i;
		for (i=0; i<3; i++)
		{
			display_string(".", 550 + i *100, 450, fb_inf, 0x00ff0000);
			usleep(200000);
		}
		for (i=0; i<3; i++)
		{
			display_string(".", 550 + i *100, 450, fb_inf, 0x00ffff55);
			usleep(200000);
		}
		c--;
	}
	/* landing mainfframe  */
	/* initialize font */
	if (init_ft("x.ttf", 32) != 0){
		fprintf(stderr, "Error initial font\n")	;
		return 1;
	}
	display_jpeg("mainframe.jpg", fb_inf);

	while (1)
	{
		int n = read(mfd, buf, 8);
		if (n != -1)
		{
			mouse_parse(buf,&mevent);
			fb_restorecursor(fb_inf, m_x, m_y);

			m_x += mevent.x;
			m_y += mevent.y;
			int k = 1;
			if (m_x>0 && m_x<1024 && m_y>0 && m_y<752)
			{
				fb_drawcursor(fb_inf, m_x, m_y);
				int i;
				for (i=0; i<9; i++)
					if (m_x > fkey[i].x && m_x < fkey[i].x + 100 && m_y > fkey[i].y &&
						m_y < fkey[i].y + 100 )
					{
						display_string(discription[i], fkey[i].x + 120, fkey[i].y + 50, fb_inf, 0x00ff0000);
						int m, n;
						for (m=fkey[i].y; m< fkey[i].y + 120; m++ )
							for (n=fkey[i].x - 20; n< fkey[i].x + 100; n++ )
								fb_pixel(b_inf, n, m, buf32[n + m * b_inf.w]);
						k = 0;

						/* interface for effect */
						if (mevent.button == 1) /* if left button down ,when the cursor 
												   is being on the taiji ico occur */
						{
							if (i == 5)
							{
								/* initialize font */
								if (init_ft("x.ttf", 64) != 0){
									fprintf(stderr, "Error initial font\n")	;
									return 1;
								}

								char *f2[7] = {"虽","然", "哥", "不", "在", "江", "湖"};
								char *f3[12] = {"但", "江", "湖", "仍", "有", "哥", "的", "传", "说", ".", ".", ".",};
								fb_info fbinf;
								if (init_fb(&fbinf) < 0)
								{
									printf("Error init_fb\n");
									exit(1);
								}

								jpgdsp_door( "oba.jpg", fbinf );
								int i;
								for (i=0; i<7; i++)
								{
									display_string(f2[i], 240 + i*80, 400, fb_inf, 0x00fffb55);
									usleep(100000);
								}
								for (i=0; i<12; i++)
								{
									display_string(f3[i], 100 + i*80, 570, fb_inf, 0x00fffb55);
									usleep(100000);
								}
								sleep(2);

								/* recover font */
								if (init_ft("x.ttf", 32) != 0){
									fprintf(stderr, "Error initial font\n")	;
									return 1;
								}
								/* interface for you */

								fbb();
								/* write here */						
								mevent.button = 0; /* Avoid play again */
								display_jpeg("mainframe.jpg", fb_inf);/* back to mainframe */
							}
						if (i == 7 && door2)
							{
								display_jpeg("show.jpg", fb_inf);
								sleep(5);
								display_jpeg("show_us.jpg", fb_inf);
								sleep(5);
								door2 = 0;
								display_jpeg("mainframe.jpg", fb_inf);
							}
							if (i == 8)
							{
								/* initialize font */
								if (init_ft("x.ttf", 64) != 0){
									fprintf(stderr, "Error initial font\n")	;
									return 1;
								}
							//	move1("log-out.jpg", fb_inf);
								display_jpeg("log-out.jpg", fb_inf);
								int i;
								char *f1[5] = {"待","续", ".", ".", "."};
								for (i=0; i<5; i++)
								{
									display_string(f1[i], 300 + i *100, 400, fb_inf, 0x00ff0000);
									usleep(100000);
								}
								int j = 4; /* replay ... tree times */
								while (j)
								{
									for (i=2; i<5; i++)
									{
										display_string(f1[i], 300 + i *100, 400, fb_inf, 0x00ffff55);
										usleep(200000);
									}
									for (i=2; i<5; i++)
									{
										display_string(f1[i], 300 + i *100, 400, fb_inf, 0x00ff0000);
										usleep(200000);
									}
									j--;
								}
								/* initialize font */
								if (init_ft("x.ttf", 32) != 0){
									fprintf(stderr, "Error initial font\n")	;
									return 1;
								}
								display_string("雁留声工作室", 800, 720, fb_inf, 0x0055ffff);
								exit(1);
							}

						}
					}
			}
			else
			{
				m_x -= mevent.x;
				m_y -= mevent.y;
			}
			if (k)
			{
				display_jpeg("mainframe.jpg", fb_inf);
				mevent.button = 0;

			}

		}
	}

	free(buf24);
	free(scale_buf);
	free(buf32);


	return 0;
}



