#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

unsigned int pixcan_width;
unsigned int pixcan_height;
unsigned int pixcan_size;

SDL_Event pixcan_event;

SDL_Window * pixcan_window;

SDL_Renderer * pixcan_renderer;

SDL_Texture * pixcan_texture;

uint32_t * pixcan;

void pixcan_init( char * title, unsigned int width, unsigned int height )
{
	pixcan_width = width;
	pixcan_height = height;
	pixcan_size = width * height;

	SDL_Init( SDL_INIT_VIDEO );

	pixcan_window = SDL_CreateWindow
	(
		title,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		pixcan_width,
		pixcan_height,
		0
	);
	
	pixcan_renderer = SDL_CreateRenderer( pixcan_window, -1, 0 );

	pixcan_texture = SDL_CreateTexture
	(
		pixcan_renderer,
		SDL_PIXELFORMAT_ABGR8888, /* on little-endian, byte order is sanely RGBA */
		SDL_TEXTUREACCESS_STATIC,
		pixcan_width,
		pixcan_height
	);

	pixcan = malloc( pixcan_width * pixcan_height * sizeof( uint32_t ) );
}

void pixcan_quit( void )
{
	SDL_DestroyTexture( pixcan_texture );
	SDL_DestroyRenderer( pixcan_renderer );
	SDL_DestroyWindow( pixcan_window );
	SDL_Quit();
	free( pixcan );
	exit( 0 );
}

#define pixcan_at( x, y ) ( pixcan[ ( x ) + ( y ) * pixcan_width ] )

uint32_t pixcan_color( uint8_t r, uint8_t g, uint8_t b )
{
	return (uint32_t)( 0xFF000000 ) | ( b << 16 ) | ( g << 8 ) | ( r );
}

void pixcan_update( void )
{
	SDL_UpdateTexture( pixcan_texture, NULL, pixcan, pixcan_width * sizeof( uint32_t ) );
	
	SDL_RenderCopy( pixcan_renderer, pixcan_texture, NULL, NULL );
	SDL_RenderPresent( pixcan_renderer );
}

bool pixcan_poll( void )
{
	SDL_PollEvent( &pixcan_event );
	if ( pixcan_event.type == SDL_QUIT ) pixcan_quit();

	SDL_Delay( 10 ); /* avoid gobbling CPU in naive loops */
	return 1;
}

void pixcan_wait( double seconds )
{
	int i;
	for ( i = 0; i < seconds * 100.0; i++ )
	{
		SDL_PollEvent( &pixcan_event );
		if ( pixcan_event.type == SDL_QUIT ) pixcan_quit();

		SDL_Delay( 10 );
	}
}


