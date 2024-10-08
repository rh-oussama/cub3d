#ifndef CUB3D_H
#define CUB3D_H

/* Libraries */
#include <X11/keysym.h>
#include <X11/X.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



/* Macros */
#define FIELD_OF_VIEW_ANGLE (60 * (M_PI / 180.0)) 
#define TILE_SIZE 32
#define NUM_TILES_WIDTH 15
#define NUM_TILES_HEIGHT 11
#define WINDOW_WIDTH (NUM_TILES_WIDTH * TILE_SIZE)
#define WINDOW_HEIGHT (NUM_TILES_HEIGHT * TILE_SIZE)

#define SCALE 1
// SPEED
#define PLAYER_SPEED 0.2
#define ROTATION_SPEED 0.2

// PI
#define PI_180 3.141592653589793 // 180 degree
#define PI_90 (PI_180 / 2) // 90 degree
#define PI_270 (3 * PI_90) // 270 degree
#define PI_360 (2 * PI_180) // 360 DEGREE

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
typedef struct s_ray
{
   double xintercept; // X coordinate of the first intersection
   double yintercept; // Y coordinate of the first intersection
   double xstep;      // Step in the X direction
   double ystep;      // Step in the Y direction
   double angle;
} t_ray;

typedef struct s_player
{
   double	x;
   double	y;
   int	r;         // Radius
	size_t speed;
   t_ray ray;     // Ray for ray casting
} t_player;


typedef struct s_img
{
   void *img;
   char *img_data;
   int bits_per_pixel;
   int size_line;       // Size of a line in bytes
   int endian;
} t_img;

typedef struct s_key
{
	int key_w;     
	int key_a;     
	int key_s;     
	int key_d;     
	int key_left;
	int key_right;

} t_key;

typedef struct s_data
{
   void 	*mlx_ptr;
   void 	*mlx_win;
   char 	**map;
   t_key key;
   t_img img;
   t_player p;
} t_data;

/* Function Prototypes */
void fill_tail(t_data *data, int x, int y, int color);
void ground_draw(t_data *data);
void player_draw(t_data *data);
void set_pixel_color(t_data *data, int x, int y, int color);
int game_render(t_data *data);
int get_pixel_index(t_data *data, int x, int y);
int print_key_press(int keysym, t_data *data);
void clear_image(t_data *data);
void update_player_position(t_data *data);
void ray_draw(t_data *data);
int key_pressed(int keysym, t_data *data);
int key_released(int keysym, t_data *data);
void update_player_rotation(t_data *data);
void	draw_line(t_data *data, int x2, int y2);
char	get_type(t_data *data, int pixel_x, int pixel_y);

void	bresenham_line(t_data *data, int x0, int y0, int x1, int y1, int color);


// RACYCASTING //

void		get_horizonntal(t_data *data, double angle);
void		get_vertical(t_data *data, double angle);
double	*get_horizontal_xyd(t_data *data, double angle);
double	*get_vertical_xyd(t_data *data, double angle);
double	*best_intersaction(t_data *data, double angle);



#endif