#include "cub3d.h"

char	*mapi[] = {
	"111111111111111",
	"1000010000000000000000000001",
	"1000110000000000000000010001",
	"1000110000000000000000010001",
	"1111111111111111111111111111",
	NULL,
};

int	get_pixel_index(t_data *data, int x, int y)
{
	return (y * data->size_line) + (x * (data->bits_per_pixel / 8));
}

void	fill_tail(t_data *data, int x, int y, int color)
{
	int	pixel;
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			pixel = get_pixel_index(data, x + j, y + i);
			data->img_data[pixel] = color & 0xFF;             // Blue component
			data->img_data[pixel + 1] = (color >> 8) & 0xFF;  // Green component
			data->img_data[pixel + 2] = (color >> 16) & 0xFF; // Red component
			data->img_data[pixel + 3] = (color >> 24) & 0xFF;
			j++;
		}
		i++;
	}
}

void	image_draw(t_data *data)
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
				fill_tail(data, x * TILE_SIZE, y * TILE_SIZE, COLOR_RED);
			else
				fill_tail(data, x * TILE_SIZE, y * TILE_SIZE, COLOR_WHITE);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);
}

/* Function to handle key press events */
int	print_key_press(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		exit(1);
	printf("key pressed: %d\n", keysym);
	return (0);
}

int	main(void)
{
	t_data	data;

	data.map = mapi;
	data.mlx_ptr = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
			"hello");
	data.img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img_data = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.size_line, &data.endian);
	image_draw(&data);
	mlx_key_hook(data.mlx_win, print_key_press, &data);
	mlx_loop_hook(data.mlx_ptr, game_render, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
