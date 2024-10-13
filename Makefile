CC = cc
# CFLAGS = -Wall -Wextra -Werror
LIBS = -lXext -lX11 -lm -lmlx
SRC = *.c
TARGET = cub3d

all: clean
	$(CC) $(CFLAGS) $(SRC) $(LIBS) -o $(TARGET)
	@./$(TARGET)
	@rm -rf $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
