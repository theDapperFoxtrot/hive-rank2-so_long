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
	int		temp_map_x;
	int		temp_map_y;
	int		player_count;
	int		exit_count;
	int		collectibles_count;
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
	int			width;
	int			height;
	int			collectables;
	int			exit_x;
	int			exit_y;
	int			player_x;
	int			player_y;
}				t_game;

#endif
