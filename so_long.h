#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define WIDTH 800
# define HEIGHT 600
# define BUFFER_SIZE 32

typedef struct  s_data
{
	int		window_width;
	int		window_height;
	int		argc;
	char	**argv;
} t_data;

typedef struct  s_player
{
	int		player_x;
	int		player_y;
	int		player_steps;
	int		player_direction;

} t_player;

typedef struct  s_game
{
	char		**map;
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_player	player;
	int			width;
	int			height;
}               t_game;

#endif
