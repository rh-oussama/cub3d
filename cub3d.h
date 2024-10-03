#ifndef CUB3D_H
#define CUB3D_H

/* Libraries */
#include <X11/keysym.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

/* Macros */
#define FIELD_OF_VIEW_ANGLE (60 * (M_PI / 180.0)) // Field of view angle in radians
#define TILE_SIZE 50                             // Size of each tile in pixels
#define NUM_TILES_WIDTH 28                     // Number of tiles horizontally
#define NUM_TILES_HEIGHT 5                       // Number of tiles vertically
#define WINDOW_WIDTH (NUM_TILES_WIDTH * TILE_SIZE) // Window width in pixels
#define WINDOW_HEIGHT (NUM_TILES_HEIGHT * TILE_SIZE) // Window height in pixels

/* Colors */
#define COLOR_RED 0xFF0000
#define COLOR_GREEN 0x00FF00
#define COLOR_BLUE 0x0000FF
#define COLOR_WHITE 0xFFFFFF
#define COLOR_BLACK 0x000000
#define COLOR_YELLOW 0xFFFF00
#define COLOR_CYAN 0x00FFFF
#define COLOR_MAGENTA 0xFF00FF

/* Structs */

typedef unsigned char byte;

typedef struct s_player
{
   int x;
   int y;
} t_player;

typedef struct s_data
{
	void *mlx_ptr;
	void *mlx_win;
	void *img;
	char *img_data;
	int bits_per_pixel;
	int size_line;
	int endian;
	char **map;
} 	t_data;

int game_render(t_data *data);

#endif /* CUB3D_H */