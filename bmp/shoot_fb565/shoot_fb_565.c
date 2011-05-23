#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


static unsigned char sg_BHeader[] = {
    0x42, 0x4D, 0x36, 0x58, 0x02, 0x00, 0x00, 0x00,  0x00, 0x00, 0x46, 0x00, 0x00, 0x00, 0x28, 0x00,
    0x00, 0x00, 0x40, 0x01, 0x00, 0x00, 0xF0, 0x00,  0x00, 0x00, 0x01, 0x00, 0x10, 0x00,/*compress*/ 0x03, 0x00,
    0x00, 0x00, /*compress*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  /*调色板*/  0x00, 0xF8, 0x00, 0x00, 0xE0, 0x07, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
#define RGB565TO1555(rgb) ((unsigned short)((unsigned short)(rgb & 0x001f) | ((unsigned short)(rgb & 0xffe0) >> 1)))

void SaveBMPFile(unsigned char *raw, char *filename)
{
    unsigned short *p = (unsigned short *)raw;
    typedef unsigned int UINT;
    typedef unsigned char UCHAR;
    //UINT m_Width = 800, m_Height = 480;
    UINT m_Width = 1024, m_Height = 768;
    UINT i, j;
    printf("in saveBMP(), filename=[%s]\n", filename);
    int bmp = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if(bmp < 0)
    {
        printf("open error:%s\n", strerror(errno));
        return;
    }
    sg_BHeader[0x02] = (UCHAR)(m_Width * m_Height * 2 + 0x36) & 0xff;
    sg_BHeader[0x03] = (UCHAR)((m_Width * m_Height * 2 + 0x36) >> 8) & 0xff;
    sg_BHeader[0x04] = (UCHAR)((m_Width * m_Height * 2 + 0x36) >> 16) & 0xff;
    sg_BHeader[0x05] = (UCHAR)((m_Width * m_Height * 2 + 0x36) >> 24) & 0xff;
    sg_BHeader[0x12] = (UCHAR)m_Width & 0xff;
    sg_BHeader[0x13] = (UCHAR)(m_Width >> 8) & 0xff;
    sg_BHeader[0x14] = (UCHAR)(m_Width >> 16) & 0xff;
    sg_BHeader[0x15] = (UCHAR)(m_Width >> 24) & 0xff;
    sg_BHeader[0x16] = (UCHAR)m_Height & 0xff;
    sg_BHeader[0x17] = (UCHAR)(m_Height >> 8) & 0xff;
    sg_BHeader[0x18] = (UCHAR)(m_Height >> 16) & 0xff;
    sg_BHeader[0x19] = (UCHAR)(m_Height >> 24) & 0xff;
    write(bmp, sg_BHeader, sizeof(sg_BHeader));
    for(i = 0; i < m_Height; i++)
    {
        unsigned short *c = p + (m_Height - 1 - i) * m_Width;
        unsigned short cc;
        for(j = 0; j < m_Width; j++)
        {
//            cc = RGB565TO1555(*(c + j));
            cc = *(c + j);
            write(bmp, &cc, 2);
        }
    }
    close(bmp);
}

int main(int argc, char *argv[])
{
    //unsigned char buf[800*480*2];
    unsigned char buf[1024*768*2];
    char *filename = "screenshot.bmp";
    int fb;
    fb = open("/dev/fb0", O_RDONLY);
    if(fb < 0)
    {
	perror("open /dev/fb0 error:");
        exit(1);
    }
    if(argc == 2)
        filename = argv[1];
    printf("in main(), filename=[%s]\n", filename);
    printf("reading screen...\n");
    //read(fb, buf, 800*480*2);
    read(fb, buf, 1024*768*2);
    close(fb);
    printf("saving screen...\n");
    SaveBMPFile(buf, filename);
    printf("file %s created successfully\n", filename);
    exit(0);
}
