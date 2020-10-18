#include "../pixcan.h"

int main( int argc, char * * argv )
{
	pixcan_init( "example", 256, 256 );

	bool invert = 0;
	for ( ;; )
	{
		unsigned int x, y;
		for ( x = 0; x < pixcan_width;  x++ )
		for ( y = 0; y < pixcan_height; y++ )
		{
			if ( invert ) pixcan_at( x, y ) = pixcan_color( 0xFF - x, 0xFF - y, x ^ y );
			else pixcan_at( x, y ) = pixcan_color( x, y, x ^ y );
		}
	
		pixcan_update();
		pixcan_wait( 1.0 );
		invert = !invert;
	}
	pixcan_quit();
	return 0;
}
