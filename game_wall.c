// #include "cub3d.h"
// #include <stdio.h>

// int wall_heigh(double *xyd)
// {
//     double d_window;
//     double w_height;

//     d_window = (WINDOW_WIDTH / 2) * tan(FIELD_OF_VIEW_ANGLE / 2);
//     w_height = (xyd[2] / TILE_SIZE) * d_window;
//     return (int) w_height;
// }

// void draw_wall(t_data *data, double *xyd, int i)
// {
//    int x, y;
//    int heigh = wall_heigh(xyd);
//    int start_y = (WINDOW_HEIGHT / 2) - (heigh / 2);
//    double rays = FIELD_OF_VIEW_ANGLE / (FIELD_OF_VIEW_ANGLE / data->img_2d.width);

	
// 	int slice_size = WINDOW_WIDTH / (int) rays;

//    printf("Wall height: %d\n", heigh);
//    printf("Start Y: %d\n", start_y);
//    printf("Slice size: %d\n", slice_size);

//    x = 0;
//    y = 0;
//     while (y <= heigh)
//     {
//         x = 0;
//         while (x <= slice_size)
//         {
//             int pixel_x = i * slice_size + x;
//             int pixel_y = start_y + y;
//             set_pixel_color(&(data->img_3d), pixel_x, pixel_y, COLOR_BLUE);
//             x++;
//         }
//         y++;
//     }
// }