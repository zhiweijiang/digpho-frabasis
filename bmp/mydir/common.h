#ifndef __COMMON_H__
#define __COMMON_H__

typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef unsigned int u32_t;

typedef struct 
{
	int w;				  /* width */
	int h;				  /* high */
	int bpp;				  /* bits per pixel */
	u8_t *fbmem;
}fb_info;

/* ******************** fb.c ******************** */

/* initial framebuf */
extern int init_fb(fb_info *fb_inf);

/* drawing pixel */
extern int fb_pixel(fb_info fb_inf, int x, int y, u32_t color);
extern int fb_line(fb_info fb_inf, int x1, int y1, int x2, int y2, u32_t 
                    color);
extern int fb_cirle(fb_info fb_inf, int x0, int y0, int r, u32_t color);
extern int fb_left_half_cirle(fb_info fb_inf, int x0, int y0, int r, u32_t color);

/* Framebuffer Test */
int fb_test(void);


/* ******************** jpeg.c ******************** */

/*This returns an array for a 24 bit image.*/
extern u8_t *decode_jpeg(const char *filename, fb_info *jpeg_inf);
extern u8_t *decode_jpeg1(const char *filename, fb_info *jpeg_inf);

extern u32_t * rgb24to32(u8_t *buf24, fb_info jpeg_inf);
extern u16_t * rgb24to16(u8_t *buf24, fb_info jpeg_inf);

extern u8_t * scale24(u8_t *buf24, fb_info new_inf, fb_info jpeg_inf);


/* ******************** disp_jpeg.c ******************** */
/* display jpeg */
extern int display_jpeg(char *filename, fb_info fb_inf);
extern int disp_roller(fb_info fb_inf, u32_t *buf32);
extern int disp_flashed(fb_info fb_inf, u32_t *buf32);
extern int disp_uptodown(fb_info fb_inf, u32_t *buf32);
extern int disp_cirle(fb_info fb_inf, u32_t *buf32);

/* ******************** font.c ******************** */
extern int init_ft (const char *file, int size);
extern int display_string (const char *buf, int x, int y, fb_info fb_inf,u32_t color);


/* ******************** mouse.c ******************** */
extern int test_mouse(fb_info fb_inf);

/* ******************** disp-basic.c ******************** */
/* create jpeg middle data file */
extern int create_jpeg(const char *filejpeg, const char *newfile, fb_info fb_inf);
/* use middle data file to display */
extern int basic_disp(const char * filename, fb_info fb_inf);


#endif
