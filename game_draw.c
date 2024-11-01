#include "cub3d.h"

void	clear_image(t_img *img, unsigned int COLOR)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			set_pixel_color(img, x, y, COLOR);
			x++;
		}
		y++;
	}
}
void	draw_floor(t_img *img, unsigned int COLOR)
{
	int	x;
	int	y;

	x = 0;
	y = img->height / 2;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			set_pixel_color(img, x, y, COLOR);
			x++;
		}
		y++;
	}
}

void	fill_tail(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE - 1)
	{
		j = 0;
		while (j < TILE_SIZE - 1)
		{
			set_pixel_color(&(data->img_2d), x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	ground_draw(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				fill_tail(data, x * TILE_SIZE, y * TILE_SIZE, COLOR_GREEN);
			else if (data->map[y][x] == '0' || data->map[y][x] == 'W' || data->map[y][x] == 'N' || data->map[y][x] == 'E' || data->map[y][x] == 'S')
				fill_tail(data, x * TILE_SIZE, y * TILE_SIZE, COLOR_WHITE);
			else if (data->map[y][x] == 'D')
				fill_tail(data, x * TILE_SIZE, y * TILE_SIZE, COLOR_MAGENTA);
			x++;
		}
		y++;
	}
}

void	player_draw(t_data *data)
{
	int	x;
	int	y;

	x = data->p.x - data->p.r;
	while (x <= data->p.x + data->p.r)
	{
		y = data->p.y - data->p.r;
		while (y <= data->p.y + data->p.r)
		{
			set_pixel_color(&(data->img_2d), x, y, COLOR_BLUE);
			y++;
		}
		x++;
	}
}

void	draw_vertical_horizontal(t_data *data, int x2, int y2)
{
	if (x2 == (int)data->p.x)
	{
		while (y2 != (int)data->p.y)
		{
			set_pixel_color(&(data->img_2d), x2, y2, COLOR_RED);
			if (y2 > data->p.y)
				y2--;
			else
				y2++;
		}
		return ;
	}
	if (y2 == (int)data->p.y)
	{
		while (x2 != (int)data->p.x)
		{
			set_pixel_color(&(data->img_2d), x2, y2, COLOR_RED);
			if (x2 > data->p.x)
				x2--;
			else
				x2++;
		}
		return ;
	}
}

/* Line Equation y = mx + b */
void	draw_line(t_data *data, int x2, int y2)
{
	double	m;
	double	b;
	int		x;
	int		y;

	if (y2 == data->p.y || x2 == data->p.x)
	{
		draw_vertical_horizontal(data, x2, y2);
		return ;
	}
	m = (float)(y2 - data->p.y) / (float)(x2 - data->p.x);
	b = data->p.y - m * data->p.x;
	if (fabs(x2 - data->p.x) > fabs(y2 - data->p.y))
	{
		x = data->p.x;
		while (x != x2)
		{
			y = (int)(m * x + b);
			set_pixel_color(&(data->img_2d), x, y, COLOR_MAGENTA);
			if (x2 > data->p.x)
				x += 1;
			else
				x += -1;
		}
	}
	else
	{
		y = data->p.y;
		while (y != y2)
		{
			x = (int)((y - b) / m);
			set_pixel_color(&(data->img_2d), x, y, COLOR_MAGENTA);
			if (y2 > data->p.y)
				y += 1;
			else
				y += -1;
		}
	}
}

int get_pixel_drawer(t_texture *texture, int x, int y)
{
    int color;
    char *pixel;

    if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
        return 0;

    pixel = texture->data + (y * texture->size_line + x * (texture->bpp / 8));
    color = *(int *)pixel;
    return color;
}

void draw_wall(t_data *data, t_ray *ray, int x)
{
    double project_plane;
    double correct_distance;
    double wall_heigh;
    double wall_top;
    int count;
    int texture_x;
    int texture_y;
    int color;

    correct_distance = ray->distance * cos(ray->angle - data->p.angle);

    project_plane = (WINDOW_WIDTH / 2) / tan(FIELD_OF_VIEW_ANGLE / 2);
    wall_heigh = (TILE_SIZE / correct_distance) * project_plane;
    wall_top = (WINDOW_HEIGHT / 2) - (wall_heigh / 2);

	double hit_point = 0;
	if (ray->hit_horizontal == 0)
		hit_point = ray->y;
	else
		hit_point = ray->x;
    texture_x = ((int)hit_point) % (TILE_SIZE * 1280);

    count = 0;
    while (count < wall_heigh)
    {
        int y = wall_top + count;
		texture_y = ((count * (853)) / wall_heigh);
		color = get_pixel_drawer((t_texture *)&(data->textures[0]), texture_x, texture_y);
		set_pixel_color(&data->img_3d, x, y, color);
        count++;
    }
}

void ray_draw(t_data *data)
{
	int i = 0;
	double angle;

	angle =  data->p.angle - (FIELD_OF_VIEW_ANGLE / 2);
	while (i < NUM_RAYS)
	{
		best_intersaction(data, angle, i);
		// draw_line(data, (int)(data->p.ray[i].x) , (int)(data->p.ray[i].y));
		draw_wall(data, &(data->p.ray[i]), i);
		angle += FIELD_OF_VIEW_ANGLE / NUM_RAYS;
		i++;
	}
}


void draw_mini_map(t_data *data, int x, int y)
{
	int	start_x;
	int	start_y;
	int	color;

	start_x = (int) data->p.x - (MINI_WIDTH / 2);
	start_y = (int) data->p.y - (MINI_HEIGHT / 2);
	y = 0;
	while (y < MINI_HEIGHT)
	{
		x = 0;
		while (x < MINI_WIDTH)
		{
			color = get_pixel_color(data, start_x + x, start_y + y);
			set_pixel_color(&data->img_3d,x, y, color);
			x++;
		}
		y++;
	}
}
