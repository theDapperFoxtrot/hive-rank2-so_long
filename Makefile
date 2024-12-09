NAME = so_long
LIBMLX = ./MLX42
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
SRC = main_so_long.c
OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a
HEADERS	= -I $(LIBMLX)/include
LIBS = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

all: .libmlx_cloned $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBS) $(HEADERS) -o $(NAME)

.libmlx_cloned:
	git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX) && touch .libmlx_cloned
	cmake $(LIBMLX) -B $(LIBMLX)/build && cmake --build $(LIBMLX)/build -j4

#libmlx: .libmlx_cloned

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)
	rm -f .libmlx_cloned
	rm -fr ./MLX42

re: fclean all
