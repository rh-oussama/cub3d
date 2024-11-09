NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address
LIBS = -lmlx -lXext -lX11 -lm
RM = rm -rf
SRC = 	mandatory/gnl/get_next_line.c \
		mandatory/gnl/get_next_line_utils.c \
		mandatory/game_libft.c \
		mandatory/game_tools_2.c \
		mandatory/game_move.c \
		mandatory/game_parsing_map.c \
		mandatory/game_parsing_map_helper.c \
		mandatory/game_parsing_map_helper2.c \
		mandatory/game_parsing_map_helper3.c \
		mandatory/game_parsing_map2.c \
		mandatory/game_parsing_textures.c \
		mandatory/game_parsing_colors.c \
		mandatory/game_parsing_tools.c \
		mandatory/game_parsing_tools2.c \
		mandatory/game_path_checker.c \
		mandatory/game_raycasting.c \
		mandatory/game_tools.c \
		mandatory/game_wall.c \
		mandatory/exit_and_free.c \
		mandatory/exit_and_free2.c \
		mandatory/main.c \

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean
	make all

.SECONDARY: