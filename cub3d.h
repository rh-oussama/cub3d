/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:59:13 by oussama           #+#    #+#             */
/*   Updated: 2024/11/13 20:31:17 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*______ For Linux _______*/

# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define MINI_WIDTH 250
# define MINI_HEIGHT 150

/*_______________________*/

/* Libraries */
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define MOUSE_SENSITIVITY 0.002

// PI
# define PI_180 3.141592653589793
# define PI_90 1.5707963268
# define PI_270 4.7123889804
# define PI_360 6.2831853072

# define SCALE 0.5
# define SAFE_DISTANCE 5

/* TILE  */
# define TILE_SIZE 32

/* FOV && RAYS */
# define FIELD_OF_VIEW_ANGLE 1.04719755
# define NUM_RAYS WINDOW_WIDTH

// SPEED
# define PLAYER_SPEED 1
# define ROTATION_SPEED 2
# define COLLISION_SPEED 2

/* Colors */
# define COLOR_RED 0xFF0000
# define COLOR_GREEN 0x00FF00
# define COLOR_BLUE 0x0000FF
# define COLOR_WHITE 0xFFFFFF
# define COLOR_BLACK 0x000000
# define COLOR_YELLOW 0xFFFF00
# define COLOR_CYAN 0x00FFFF
# define COLOR_MAGENTA 0xFF00FF

// gnl
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# define RAW_SIZE 20
/* Structs */
typedef struct s_ray
{
	double		x;
	double		y;
	double		type;
	double		angle;
	double		distance;
	int			hit_horizontal;
	int			looking_down;
	int			looking_left;
}				t_ray;

typedef struct s_player
{
	double		x;
	double		y;
	double		angle;
	int			r;
	size_t		speed;
	t_ray(ray)[NUM_RAYS];
}				t_player;

typedef struct s_img
{
	void		*img;
	char		*img_data;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_key
{
	int			key_w;
	int			key_a;
	int			key_s;
	int			key_d;
	int 		key_j;
	int			key_sp;
	int			key_q;
	int			key_left;
	int			key_right;
}				t_key;

typedef struct s_texture
{
	void		*img;
	int			width;
	int			height;
	char		*data;
	int			size_line;
	int			endian;
	int			bpp;

}				t_texture;

typedef struct s_project
{
	double		proj_plane;
	double		wall_height;
	double		wall_top;
	double		hit_point;
	int			tex_x;
	int			tex_y;
	int			tex_size;
	t_texture	*textures;
}				t_project;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*mlx_win;

	char		*floor;
	char		*ceiling;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;

	char		**floor_parse;
	char		**ceiling_parse;
	char		**map;
	char		**map_checker;
	char		**new_map;
	char		**door;

	int			floor_color;
	int			ceiling_color;
	int			width;
	int			height;
	int			co_x;
	int			co_y;
	int			r;
	int			g;
	int			b;

	t_project	pr_info;
	t_key		key;
	t_img		img_2d;
	t_img		img_3d;
	t_player	p;
	t_texture	textures[6];
	t_texture	first[58];
	t_texture	second[101];
	t_texture	third[14];
	t_texture	fourth[122];
}				t_data;

/* Function Prototypes */

// Game Rendering
int				game_render(t_data *data);

// Game movement
void			update_player_position(t_data *data);
void			update_player_rotation(t_data *data);
void			set_pixel_color(t_img *img, int x, int y, int color);
double			normalize_angle(double angle);
int				is_wall(t_data *data, double *xyd, double angle, char type);
void			move_player(t_data *data, double angle);
int				is_safe(t_data *data, double x, double y);

// Event Handling
int				key_pressed(int keysym, t_data *data);
int				key_released(int keysym, t_data *data);

// Parsing
void			error_msg(char *str, t_data *game);
void			error(char *str);
char			*ft_itoa(int n);
void			error_msg_2(char *str, t_data *game);
int				ft_atoi(char *str, t_data *game);
int				ft_isalpha_num(int i);
int				ft_is_num(int i);
char			**ft_split(char *s, char c);
char			*ft_strtrim(char *s1);
char			*ft_copy(char *s1, int len);
void			line_check(char *game, t_data *data, char *trimmed);
void			checker(char *game, char c, t_data *data);
void			get_color(t_data *game);
void			get_textures(t_data *game);
void			textures_check(t_data *game);
void			check_map(t_data *game);
void			get_width(t_data *data, int x);
void			map_parsing(t_data *game, char **av);
void			map_configure(t_data *data, int x, int flag, char *trimmed);
void			is_map_closed(t_data *game);
void			get_map(t_data *data, char **av);
int				check_path(char **map);
void			first_and_last_row(t_data *game);
void			no(char *trimmed, t_data *data, int *flag);
void			so(char *trimmed, t_data *data, int *flag);
void			we(char *trimmed, t_data *data, int *flag);
void			ea(char *trimmed, t_data *data, int *flag);
char			*trim(t_data *data, int flag, int x, char *trimmed);

// free
void			free_images(t_data *game);
void			free_new_map(t_data *game);
void			free_map_checker(t_data *game);
void			free_map(t_data *game);
void			free_ceiling(t_data *game);
void			free_floor(t_data *game);
void			free_door(t_data *game);
int				exit_game(t_data *game);

// sprite
int				sprite(t_data *data, t_texture *sprite, int frames);
void			sprite_textures(t_data *game);

// Raycasting
void			get_horizonntal(t_data *data, double angle, double *xy_step,
					double *xy_xintercept);
void			get_vertical(t_data *data, double angle, double *xy_step,
					double *xy_xintercept);
void			best_intersaction(t_data *data, double angle, int i);
void			get_horizontal_xyd(t_data *data, double angle, double *xyd);
void			get_vertical_xyd(t_data *data, double angle, double *xyd);
void			add_ray(t_ray *ray, double angle, double *xyd, char type);

// Mini Map
int				get_pixel_color(t_data *data, int x, int y);

// Get Next Line (gnl)
size_t			ft_strlen(char *s);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strchr(char *s, int c);
char			*ft_substr(char *s, unsigned int start, size_t len);
char			*ft_strdup(char *s1);
char			*get_next_line(int fd);

// Drawing
int				get_pixel_col(t_texture *texture, int x, int y);
void			draw_wall_helper(t_data *data, t_ray *ray);
void			draw_wall(t_data *data, t_ray *ray, int x);
void			ray_draw(t_data *data);

// Utility
char			get_type(t_data *data, double pixel_x, double pixel_y);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_isspace(int c);
void			get_player_position(t_data *game);

// Mini Map

void			draw_line(t_data *data, double xpos, double ypos);
void			draw_mini_map(t_data *data, int x, int y);
void			fill_tail(t_data *data, int x, int y, int color);
void			ground_draw(t_data *data);
void			player_draw(t_data *data, int xpos, int ypos);

// door
char			**new_array(char **array);
void			door_mechanism(t_data *data);
void			door_mechanism(t_data *data);
int				handle_door_interaction(t_data *data, int x, int y, char type);

// Collision System
void			process_wall_collision(t_data *data, double angle);
void			handle_vertical_wall_collision(t_data *data, double angle,
					t_ray *ray);
void			handle_horizontal_wall_collision(t_data *data, double angle,
					t_ray *ray);

#endif