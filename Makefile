NAME = cub3D
NAME_BONUS = cub3D_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -I.
LIBS = -lmlx -lXext -lX11 -lm
RM = rm -rf
SRC = mandatory/gnl/get_next_line.c \
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

BSRCS = bonus/gnl/get_next_line.c \
		bonus/gnl/get_next_line_utils.c \
		bonus/game_libft.c \
		bonus/game_door.c \
		bonus/game_mini_map.c \
		bonus/game_tools_2.c \
		bonus/game_move.c \
		bonus/game_parsing_map.c \
		bonus/game_parsing_map_helper.c \
		bonus/game_parsing_map_helper2.c \
		bonus/game_parsing_map_helper3.c \
		bonus/game_parsing_map2.c \
		bonus/game_parsing_textures.c \
		bonus/game_parsing_colors.c \
		bonus/game_parsing_tools.c \
		bonus/game_parsing_tools2.c \
		bonus/game_path_checker.c \
		bonus/game_raycasting.c \
		bonus/game_tools.c \
		bonus/game_wall.c \
		bonus/exit_and_free.c \
		bonus/exit_and_free2.c \
		bonus/main.c \

BOBJS = $(BSRCS:.c=.o)

LIBS = -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

bonus: $(BOBJS)
		$(CC) $(CFLAGS) -o $(NAME_BONUS) $(BOBJS) $(LIBS)

clean:
		$(RM) $(OBJS) $(BOBJS)

fclean: clean
		$(RM) $(NAME) $(NAME_BONUS)

re: fclean all