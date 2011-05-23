/*   by  Song Yanjun

*/

#include "jpgdsp_syj.h"
#define MAXLOOP 1
int jpgdsp_movies( const char *pfname, fb_info fbinf )
{
	fb_info jpeg_inf;
	u32_t *pbuff = NULL;
	int i,j;
	int k,n;
	int col = 50;
	int col1 = 100;
	int dw = 400;
	int loop = 0;

	u8_t *buf24 = decode_jpeg( pfname, &jpeg_inf );
	u8_t * scale_buf = scale24( buf24, fbinf, jpeg_inf );
	pbuff = rgb24to32( scale_buf,  fbinf );

	free( buf24 );
	buf24 = NULL;
	free( scale_buf );
	scale_buf = NULL;


	n=0; // pbuff[0]
	while( 1 )
	{
		k=n;
		for( j=col1; j<dw; j++ )
		{
			for( i=col; i<dw*4/3; i++ )
			{
				fb_pixel(fbinf, i, j, (pbuff[i+(k)*fbinf.w]) );
			}
			k++;
			if( k>=fbinf.h )
				k = 0;
		}
		n++; //pbuff[n++]
		if( n>=fbinf.h )
		{
			n=0;
			loop++;
			if( loop == MAXLOOP )
				break;
		}

		//loop--;
		//usleep( 10000 );
	}


	free( pbuff );
	pbuff = NULL;

	return 0;
}

