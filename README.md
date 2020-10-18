pixcan
======

**pixcan** is a convenient header-only "pixel canvas" library based on SDL2.
It's a quick and painless way to prototype and experiment with graphics programming in C.
While designed primarily for educational use, it's straightforward enough for those
familiar with SDL2 to add user input, audio, and more.

Usage
-----

For the impatient:
1. `#include "pixcan.h"`.
2. Call `pixcan_init`.
3. Modify the `pixcan_size`-sized buffer of RGBA8 pixels pointed to by `pixcan`.
4. Call `pixcan_update` to synchronize the buffer with the screen.
5. Call `pixcan_poll` in a loop to keep the window open until `Escape` is pressed. 
6. Compile with `cc `sdl-config --cflags` -o <program> <program>.c -lSDL2 -lm`.

### Here are the exposed global variables and functions.

`unsigned int pixcan_width`
The width, in pixels, of the canvas.

`unsigned int pixcan_height`
The height, in pixels, of the canvas.

`unsigned int pixcan_size`
The size, in pixels, of the canvas. Equivalent to `pixcan_width * pixcan_height`.

`uint32_t * pixcan`
A pointer to `pixcan_size` `uint32_t`s, each one pixel on the canvas in row-major order. See ***Notes***.


`void pixcan_init( char * title, unsigned int width, unsigned int height )`
Initializes the canvas, opening a new `width`-by-`height` window with the provided title.

`void pixcan_quit()`
Closes the window, deallocates all of pixcan's resources, and terminates the program.

`pixcan_at( x, y )` 
A macro that expands to `pixcan[ ( x ) + ( y ) * pixcan_width ]`. See ***Notes***.

`uint32_t pixcan_color( uint8_t r, uint8_t g, uint8_t b )`
Given red, green, and blue byte values, returns a pixel suitable for storage in `pixcan`.

`void pixcan_update()`
Synchronizes the contents of the window with the pixel buffer `pixcan`.

`bool pixcan_poll()`
Keeps the window open until `Escape` is pressed or the window is closed.

`void pixcan_wait( double seconds )`
Keeps the window open for roughly `seconds` seconds unless `Escape` is pressed or the window is closed.

Notes
-----
* Internally, pixcan actually uses `ABGR8888`. However, because your computer is little-endian, the buffer's arrangement in memory is a more reasonable `R, G, B, A`, meaning you can cast `pixcan` to a `uint8_t *` without surprises.
* Because `pixcan_at` is a macro, it can be used idiomatically as an lvalue. That is, you can write
```
pixcan_at( x, y ) = pixcan_color( r, g, b );
```
* This `README` is longer than `pixcan.h` itself. Go read it instead.

Thanks
------

http://gigi.nullneuron.net/gigilabs/sdl2-pixel-drawing/
