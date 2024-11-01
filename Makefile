NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -Imlx
LIBS = mlx_library/libmlx.a -framework OpenGL -framework AppKit
RM = rm -rf
SRC = 	game_draw.c \
		game_move.c \
		game_raycasting.c \
		game_parsing_map.c \
		game_parsing_colors.c \
		game_parsing_textures.c \
		game_parsing_tools.c \
		game_path_checker.c \
		game_tools.c \
		gnl/get_next_line.c \
     	gnl/get_next_line_utils.c \
		main.c
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean
	make all

.SECONDARY: