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

// PI
#define PI_180 3.141592653589793 // 180 degree
#define PI_90 (PI_180 / 2) // 90 degree
#define PI_270 (3 * PI_90) // 270 degree
#define PI_360 (2 * PI_180) // 360 DEGREE


/* TILE  */
#define TILE_SIZE 32
#define NUM_TILES_WIDTH 15
#define NUM_TILES_HEIGHT 11

/* WINDOW */
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

/* FOV && RAYS */
#define FIELD_OF_VIEW_ANGLE (60 * (PI_180 / 180.0))
#define NUM_RAYS WINDOW_WIDTH

// SPEED
#define PLAYER_SPEED 2
#define ROTATION_SPEED 2

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
	double x;
	double y;
	double distance;
	int hit_horizontal;
	int looking_down;
	int looking_left;
	struct s_ray *next;
} t_ray;

typedef struct s_player
{
   double	x;
   double	y;
   double 	angle;
	int		r;
	size_t speed;
   t_ray *ray;
} t_player;


typedef struct s_img
{
   void *img;
   char *img_data;
   int bits_per_pixel;
   int size_line;
   int endian;
	int width;
	int height;
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
	int	SCALE;
   t_key key;
   t_img img_2d;
   t_img img_3d;
	t_img mini_map;
   t_player p;
} t_data;

/* Function Prototypes */
void		fill_tail(t_data *data, int x, int y, int color);
void		ground_draw(t_data *data);
void		player_draw(t_data *data);
int		game_render(t_data *data);
void		update_player_position(t_data *data);
void		ray_draw(t_data *data);
int		key_pressed(int keysym, t_data *data);
int		key_released(int keysym, t_data *data);
void		update_player_rotation(t_data *data);
void		draw_line(t_data *data, int x2, int y2);
char		get_type(t_data *data, double pixel_x, double pixel_y);
void		clear_image(t_img *img, unsigned int COLOR);
int		get_pixel_index(t_img *img, int x, int y);
void		set_pixel_color(t_img *img, int x, int y, int color);
double	normalize_angle(double angle);
int		is_wall(t_data *data, double *xyd, double angle, char type);


// RACYCASTING //
double distance(double x1 , double y1, double x2, double y2);
void get_horizonntal(t_data *data, double angle, double *xy_step, double *xy_xintercept);
double *get_horizontal_xyd(t_data *data, double angle);
void get_vertical(t_data *data, double angle, double *xy_step, double *xy_xintercept);
double *get_vertical_xyd(t_data *data, double angle);
void	best_intersaction(t_data *data, double angle);



void add_ray(t_data *data, double angle, double *xyd, char type);
t_ray	*add_ray_helper(double angle, double *xyd, char type);
void free_ray(t_data *data);


#endif