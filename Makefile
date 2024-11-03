NAME = cub3d
CC = cc
RM = rm -rf
CFLAGS =  -pg # -Wall -Wextra -Werror

## LINUX MAC LIB ##
CLIBS = mlx_library/libmlx.a -framework OpenGL -framework AppKit -lmlx
ifeq ($(shell uname), Linux)
   CLIBS = -lXext -lX11 -lm -lmlx -pg
endif
##

SRC =		game_draw.c \
			game_libft.c \
			game_move.c \
			game_parsing_colors.c \
			game_parsing_map.c \
			game_parsing_textures.c \
			game_parsing_tools.c \
			game_path_checker.c \
			game_raycasting.c \
			game_tools.c \
			game_wall.c \
			main.c \
			gnl/get_next_line.c \
			gnl/get_next_line_utils.c \

OBJS = $(SRC:.c=.o)

all: $(NAME)
	make clean

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(CLIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(CLIBS) -c $< -o $@

run: $(NAME)
	./$(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

