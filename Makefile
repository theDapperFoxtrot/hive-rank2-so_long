NAME = so_long
LIBMLX = ./lib/MLX42
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
SRC = main_so_long.c
OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a
LIBS = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

all: libmlx $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

.libmlx_cloned:
	git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX)
	touch .libmlx_cloned

libmlx: .libmlx_cloned
	cmake $(LIBMLX) -B $(LIBMLX)/build
	make -C $(LIBMLX)/build -j4

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJ)
	rm -fr $(LIBMLX)/build

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)
	rm -f .libmlx_cloned
	rm -fr ./lib

re: fclean all
