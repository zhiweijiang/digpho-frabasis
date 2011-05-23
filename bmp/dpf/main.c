#include<stdio.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<linux/fb.h>
#define FB_DEVICE "/dev/fb0"

int main(int argc, char * argv[])
{
	int fd;
	fd = open(FB_DEVICE, O_RDWR);
	if(fd < 0) {
		fprintf(stderr, "Errer open file %s: %s\n", FB_DEVICE, strerror(errno));
		exit(1);
	}
	fprintf(stdout, "open file %s successful\n", FB_DEVICE);

	struct fb_var_screeninfo fb_var;
	
	if(ioctl(fd, FBIOGET_VSCREENINFO, &fb_var) < 0){
		fprintf(stderr, "Error ioctl: %s\n", strerror(errno));
		exit(1);
	}
	fprintf(stdout,"ioctl file %s:Success\n", FB_DEVICE);
	int w, h, bpp;

	w = fb_var.xres;
	h = fb_var.yres;
	bpp = fb_var.bits_per_pixel;

	printf("w = %d, h = %d, bpp = %d\n", w, h, bpp);

	char *fb_mem;
	if((fb_mem = mmap(NULL, w * h * bpp / 8, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == NULL)  {
		fprintf(stderr, "Error mmap file %s: %s\n", FB_DEVICE, strerror(errno));
		exit(1);
	}
	fprintf(stdout, "mmap file %s:Success\n", FB_DEVICE);

	/* w/2, h/2 */
	((int *)fb_mem)[w*h/2 + w/2] = 0xff0000; 
	int i, j; 
	for(i = 0; i < 1024; i++)
	((int *)fb_mem)[w*h/3 +i] = 0xff0000; 
	i = 0;
	for(j = 0; j < 400; j++)
		((int *)fb_mem)[w*h/3 +(i++)*512+j] = 0xff0000; 
	i = 400;
	for(j = 0; j < 400; j++)
		((int *)fb_mem)[w*h/3 +(i--)*512+j] = 0xff0000; 

	close(fd);
	
	return 0;
}
