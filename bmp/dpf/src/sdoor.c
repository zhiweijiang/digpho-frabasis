#include "jpgdsp_syj.h" 

int jpgdsp_door( const char *pfilename, fb_info fbinf  )
{
	fb_info jpeg_inf;
	
	u8_t *buf24 = decode_jpeg(pfilename, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fbinf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fbinf);
	//u32_t *buf_thunder = (u32_t *)malloc( fbinf.w*fbinf.h*4 );

	int i, j, k;
	int tmp;
	int n;

	for ( i=fbinf.w/2-1; i>=0; i-- )
	{
		for( k=0; k<=fbinf.w/2-i; k+=3 )
			for( j=0; j<fbinf.h; j++ )
			{
				tmp = buf32[k + j * fbinf.w];
				fb_pixel(fbinf, i+k, j, tmp );
				if( k - 1 >= 0 )
				{
					tmp = buf32[k-1 + j * fbinf.w];
					fb_pixel(fbinf, i+k-1, j, tmp );
				}
				if( k - 2 >= 0 )
				{
					tmp = buf32[k-2 + j * fbinf.w];
					fb_pixel(fbinf, i+k-2, j, tmp );
				}
			}
		for( k=fbinf.w-1-i, n=0; k>=fbinf.w/2; k-= 3, n+=3 )
			for( j=0; j<fbinf.h; j++ )
			{
				tmp = buf32[fbinf.w-1-n + j * fbinf.w];
				fb_pixel(fbinf, k, j, tmp );
				if( k + 1 < fbinf.w && n-1 >= fbinf.w/2 )
				{
					tmp = buf32[fbinf.w-1-(n-1) + j * fbinf.w];
					fb_pixel(fbinf, k+1, j, tmp );
				}
				if( k + 2 < fbinf.w && n-2 >= fbinf.w/2 )
				{
					tmp = buf32[fbinf.w-1-(n-2) + j * fbinf.w];
					fb_pixel(fbinf, k+2, j, tmp );
				}
			}
	}
	return 0;

}
