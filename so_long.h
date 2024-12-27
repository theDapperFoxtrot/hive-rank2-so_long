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

typedef struct s_data
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
}			t_data;

typedef struct s_player
{
	int		player_x;
	int		player_y;
	int		player_steps;
	int		player_direction;
}			t_player;

typedef struct s_game
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

void	start_interface(t_game *game, mlx_t **interface);
void	handle_error(t_game *game, char *message, \
char **freedom_seekers, char *freedom_seeker);
void	init_values(t_game *game);
void	read_map(char *filename, t_game *game);
void	get_map_width_height(t_game *game, int fd, char **line);
void	*get_next_valid_line(t_game *game, int fd, char **line);
int		read_and_process_buffer(t_game *game, int fd, \
char **line, char *buffer);
int		valid_character(char c);
void	generate_map(t_game *game, int fd, char **map, char **line);
void	validate_map(t_game *game, t_player *player, t_data *data);
void	necessary_characters(t_game *game, t_player *player, t_data *data);
void	loop_necessary_characters(t_game *game, t_player *player, t_data *data);
void	loop_loop_necessary_characters(t_game *game, \
t_player *player, t_data *data, int i);
void	check_walls(t_game *game);
int		is_playable(t_game *game, t_player *player, t_data *data);
char	**create_temp_map(t_game *game);
int		flood_fill(t_game *game, \
char **temp_map, int temp_map_x, int temp_map_y);

#endif