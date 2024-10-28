NAME = cub3d
CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror

## LINUX MAC LIB ##
CLIBS = mlx_library/libmlx.a -framework OpenGL -framework AppKit -lmlx
ifeq ($(shell uname), Linux)
   CLIBS = -lXext -lX11 -lm -lmlx
endif
##

SRC =		game_draw.c \
			game_move.c \
			game_raycasting.c \
			game_parsing.c \
			game_tools.c \
			gnl/get_next_line.c \
			gnl/get_next_line_utils.c \
			main.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(CLIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(CLIBS) -c $< -o $@

run: $(NAME)
	./$(NAME)

clean:
	rm -f $(OBJS) $(NAME)

fclean: clean
	$(RM) $(NAME)

re: fclean all

