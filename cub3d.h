/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhaddao <orhaddao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:59:13 by oussama           #+#    #+#             */
/*   Updated: 2024/11/03 11:11:38 by orhaddao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// #include <string.h>
/*______ For Mac _______*/

// # include "mlx_library/mlx.h"

// #define WINDOW_WIDTH 1680
// #define WINDOW_HEIGHT 1050
// # define MINI_WIDTH 320
// # define MINI_HEIGHT 180

// #define XK_Escape      53
// #define XK_w           13
// #define XK_a           0
// #define XK_s           1
// #define XK_d           2
// #define XK_Left        123
// #define XK_Right       124
// #define XK_Up          126
// #define XK_Down        125
// #define KeyPress          2
// #define KeyRelease        3
// #define KeyPressMask      (1L<<0)
// #define KeyReleaseMask    (1L<<1)

/*_______________________*/

/*______ For Linux _______*/

# include <X11/keysym.h>
# include <X11/X.h>
# include <mlx.h>

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define MINI_WIDTH 320
# define MINI_HEIGHT 180

/*_______________________*/




/* Libraries */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>

// PI
# define PI_180 3.141592653589793
# define PI_90 (PI_180 / 2)
# define PI_270 (3 * PI_90)
# define PI_360 (2 * PI_180)

# define SCALE 0.5
# define PIXELS_AHEAD 0

/* TILE  */
# define TILE_SIZE 32


/* FOV && RAYS */
# define FIELD_OF_VIEW_ANGLE (60 * (PI_180 / 180.0))
# define NUM_RAYS WINDOW_WIDTH

// SPEED
# define PLAYER_SPEED 3
# define ROTATION_SPEED 9

/* Colors */
# define COLOR_RED 0xFF0000
# define COLOR_GREEN 0x00FF00
# define COLOR_BLUE 0x0000FF
# define COLOR_WHITE 0xFFFFFF
# define COLOR_BLACK 0x000000
# define COLOR_YELLOW 0xFFFF00
# define COLOR_CYAN 0x00FFFF
# define COLOR_MAGENTA 0xFF00FF

//gnl
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# define RAW_SIZE 20
/* Structs */
typedef struct s_ray
{
	double	x;
	double	y;
	double	angle;
	double	distance;
	int		hit_horizontal;
	int		looking_down;
	int		looking_left;
}	t_ray;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	int		r;
	size_t	speed;
	t_ray		(ray)[NUM_RAYS];
}	t_player;

typedef struct s_img
{
	void	*img;
	char	*img_data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_key
{
	int	key_w;
	int	key_a;
	int	key_s;
	int	key_d;
	int	key_left;
	int	key_right;
}	t_key;

typedef struct s_texture
{
	void		*img;
	int		width;
	int		height;
	char 		*data;
	int		size_line;
	int		endian;
	int		bpp;

}				t_texture;

typedef struct s_project
{
	double proj_plane;
	double wall_height;
	double wall_top;
	double hit_point;
	int tex_x;
	int tex_y;
	int tex_size;
	t_texture	*textures;
} t_project;

typedef struct s_config
{
	/* data */
} t_config;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*mlx_win;

	char		*floor;
	char		*ceiling;
	int			floor_color;
	int			ceiling_color;
	char		**floor_parse;
	char		**ceiling_parse;

	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	
	char		**map;
	char		**map_checker;
	char		**new_map;
	
	int			width;
	int			height;

	int			player_x;
	int			player_y;
	t_project pr_info;
	t_key		key;
	t_img		img_2d;
	t_img		img_3d;
	t_img		mini_map;
	t_player	p;
	t_texture	textures[4];
}	t_data;

/* Function Prototypes */
void		fill_tail(t_data *data, int x, int y, int color);
void		ground_draw(t_data *data);
void		player_draw(t_data *data, int xpos, int ypos);
int		game_render(t_data *data);
void		update_player_position(t_data *data);
// void		ray_draw(t_data *data);
int		key_pressed(int keysym, t_data *data);
int		key_released(int keysym, t_data *data);
void		update_player_rotation(t_data *data);
void 		draw_line(t_data *data, double xpos, double ypos);
void		draw_floor(t_img *img, unsigned int COLOR);
char		get_type(t_data *data, double pixel_x, double pixel_y);
void		clear_image(t_img *img, unsigned int COLOR);
int		get_pixel_index(t_img *img, int x, int y);
void		set_pixel_color(t_img *img, int x, int y, int color);
double	normalize_angle(double angle);
int		is_wall(t_data *data, double *xyd, double angle, char type);

// PARSING //
void	error_msg(char *str);
char	*ft_strstr(char *str, char *to_find);
int	ft_atoi(const char *str);
int	ft_isalpha_num(int i);
int ft_is_num(int i);
char	**ft_split(char *s, char c);
void	get_color(t_data *game);
void	get_textures(t_data *game);
void	textures_check(t_data *game);
void	check_map(t_data *game);
void	map_parsing(t_data *game, char **av);

// RACYCASTING //
double distance(double x1 , double y1, double x2, double y2);
void get_horizonntal(t_data *data, double angle, double *xy_step, double *xy_xintercept);
void get_vertical(t_data *data, double angle, double *xy_step, double *xy_xintercept);
void	best_intersaction(t_data *data, double angle, int i);
void	get_horizontal_xyd(t_data *data, double angle, double *xyd);
void	get_vertical_xyd(t_data *data, double angle, double *xyd);

void add_ray(t_ray *ray, double angle, double *xyd, char type);

// MINI MAP
void draw_mini_map(t_data *data, int x, int y);
int get_pixel_color(t_data *data, int x, int y);

//gnl

size_t			ft_strlen(char *s);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strchr(char *s, int c);
char			*ft_substr(char *s, unsigned int start, size_t len);
char			*ft_strdup(char *s1);
char			*get_next_line(int fd);
//

int	get_pixel_drawer(t_texture *texture, int x, int y);
void	draw_wall_helper(t_data *data, t_ray *ray);
void	draw_wall(t_data *data, t_ray *ray, int x);
void	ray_draw(t_data *data);


int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_isspace(int c);

#endif