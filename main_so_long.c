#include "so_long.h"

static void	handle_error(t_game *game, char *message, \
char **freedom_seekers, char *freedom_seeker)
{
	if (freedom_seeker)
		free(freedom_seeker);
	if (freedom_seekers)
		free_split(freedom_seekers);
	free(game);
	ft_putstr_fd(message, 2);
	exit(1);
}

static int	valid_character(char c)
{
	return (c == '0' || c == '1' || c == 'C' \
	|| c == 'E' || c == 'P' || c == '\0' \
	|| c == '\n' || c == ' ' || c == '\t' \
	|| c == '\v' || c == '\f' || c == '\r');
}

static int	read_and_process_buffer(t_game *game, int fd, \
char **line, char *buffer)
{
	char	*temp;
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, 1);
		buffer[1] = '\0';
		if (buffer[0] == '\n' || buffer[0] == '\0')
			break ;
		if (buffer[0] == 32 || (buffer[0] > 9 && buffer[0] < 13))
			continue ;
		if (!valid_character(buffer[0]))
		{
			free(buffer);
			handle_error(game, "Invalid character in map\n", NULL, *line);
		}
		temp = ft_strjoin(*line, buffer);
		free(*line);
		*line = temp;
	}
	return (bytes_read);
}

static void	*get_next_valid_line(t_game *game, int fd, char **line)
{
	char	*buffer;

	buffer = (char *)malloc(2);
	if (!buffer)
		handle_error(game, "Failed to allocate buffer memory\n", NULL, NULL);
	read_and_process_buffer(game, fd, line, buffer);
	free(buffer);
	return (*line);
}

void	get_map_width_height(t_game *game, int fd, char **line)
{
	*line = NULL;
	game->height = 0;
	game->width = 0;
	while (get_next_valid_line(game, fd, line) && (*line))
	{
		if (game->height == 0)
			game->width = ft_strlen(*line);
		game->height++;
		free(*line);
		*line = NULL;
	}
}

void	generate_map(t_game *game, int fd, char **map, char **line)
{
	int		i;

	i = 0;
	while (i < game->height)
	{
		get_next_valid_line(game, fd, line);
		map[i] = ft_strdup(*line);
		if (!map[i])
			handle_error(game, \
			"Failed to allocate memory for map\n", map, *line);
		free(*line);
		*line = NULL;
		i++;
	}
	map[i] = NULL;
	close(fd);
	game->map = map;
}

static void	read_map(char *filename, t_game *game)
{
	int		fd;
	char	*line;
	char	**map;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		handle_error(game, "Failed to open file\n", NULL, NULL);
	get_map_width_height(game, fd, &line);
	close(fd);
	map = (char **)malloc(sizeof(char *) * (game->height + 1));
	if (!map)
		handle_error(game, "Failed to allocate memory\n", NULL, NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		handle_error(game, "Failed to open file\n", map, NULL);
	generate_map(game, fd, map, &line);
}

void	loop_loop_necessary_characters(t_game *game, \
t_player *player, t_data *data, int i)
{
	int	j;

	j = 0;
	while (game->map[i][j])
	{
		if (game->map[i][j] == 'P')
		{
			player->player_x = j;
			player->player_y = i;
			data->player_count++;
		}
		else if (game->map[i][j] == 'E')
		{
			game->exit_x = j;
			game->exit_y = i;
			data->exit_count++;
		}
		else if (game->map[i][j] == 'C')
			data->collectibles_count++;
		j++;
	}
}

void	loop_necessary_characters(t_game *game, t_player *player, t_data *data)
{
	int	i;

	i = 0;
	while (i < game->height)
	{
		loop_loop_necessary_characters(game, player, data, i);
		i++;
	}
}

void	necessary_characters(t_game *game, t_player *player, t_data *data)
{
	data->player_count = 0;
	data->exit_count = 0;
	data->collectibles_count = 0;
	loop_necessary_characters(game, player, data);
	if (data->player_count != 1 || \
	data->exit_count != 1 || data->collectibles_count < 1)
		handle_error(game, \
		"Necessary characters in your map are incorrect\n", game->map, NULL);
}

void	check_walls(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (game->map[i][j])
		{
			if (i == 0 || i == game->height - 1)
			{
				if (game->map[i][j] != '1')
					handle_error(game, \
					"Map is not surrounded by walls\n", game->map, NULL);
			}
			else if (j == 0 || j == game->width - 1)
			{
				if (game->map[i][j] != '1')
					handle_error(game, \
					"Map is not surrounded by walls\n", game->map, NULL);
			}
			j++;
		}
		i++;
	}
}

static char	**create_temp_map(t_game *game)
{
	int		i;
	char	**temp_map;

	temp_map = (char **)malloc(sizeof(char *) * (game->height + 1));
	if (!temp_map)
		return (NULL);
	i = 0;
	while (i < game->height)
	{
		temp_map[i] = ft_strdup(game->map[i]);
		if (!temp_map[i])
		{
			while (i > 0)
			{
				free(temp_map[i - 1]);
				i--;
			}
			free(temp_map);
			return (NULL);
		}
		i++;
	}
	temp_map[game->height] = NULL;
	return (temp_map);
}

static int	flood_fill(t_game *game, \
char **temp_map, int temp_map_x, int temp_map_y)
{
	static int	collectables = 0;
	static int	exit_found = 0;

	if (temp_map[temp_map_y][temp_map_x] == '1')
		return (0);
	else if (temp_map[temp_map_y][temp_map_x] == 'C')
		collectables++;
	else if (temp_map[temp_map_y][temp_map_x] == 'E')
	{
		exit_found = 1;
		return (0);
	}
	temp_map[temp_map_y][temp_map_x] = '1';
	flood_fill(game, temp_map, temp_map_x + 1, temp_map_y);
	flood_fill(game, temp_map, temp_map_x - 1, temp_map_y);
	flood_fill(game, temp_map, temp_map_x, temp_map_y + 1);
	flood_fill(game, temp_map, temp_map_x, temp_map_y - 1);
	if (collectables == game->collectables && exit_found)
		return (1);
	return (0);
}

int	is_playable(t_game *game, t_player *player, t_data *data)
{
	int		i;
	int		result;
	char	**temp;

	data->temp_map_x = player->player_x;
	data->temp_map_y = player->player_y;
	game->collectables = data->collectibles_count;
	temp = create_temp_map(game);
	if (!temp)
		handle_error(game, "Memory allocation failed", NULL, NULL);
	result = flood_fill(game, temp, data->temp_map_x, data->temp_map_y);
	if (!result)
	{
		free_split(temp);
		handle_error(game, "No valid path available\n", game->map, NULL);
	}
	i = 0;
	while (i < game->height)
		free(temp[i++]);
	free(temp);
	return (result);
}

void	validate_map(t_game *game, t_player *player, t_data *data)
{
	char	*current_line;
	char	*next_line;
	int		i;

	i = 0;
	if (game->height < 4 || game->width < 4)
		handle_error(game, "Map is too small\n", game->map, NULL);
	while (game->map[i])
	{
		current_line = game->map[i];
		next_line = (game->map[i + 1]);
		if ((int) ft_strlen(current_line) != game->width)
			handle_error(game, "Map is not rectangular\n", game->map, NULL);
		if (next_line == NULL)
			break ;
		i++;
	}
	necessary_characters(game, player, data);
	check_walls(game);
	is_playable(game, player, data);
}

void	init_values(t_game *game)
{
	game->map = NULL;
	game->mlx = NULL;
	game->image = NULL;
	game->width = 0;
	game->height = 0;
	game->collectables = 0;
	game->exit_x = 0;
	game->exit_y = 0;
}

void	start_interface(t_game *game, mlx_t **interface)
{
	*interface = mlx_init(WIDTH, HEIGHT, "so_long", true);
	if (!(*interface))
		handle_error(game, "Failed to initialize interface\n", NULL, NULL);
	mlx_loop(*interface);
}

int	main(int argc, char **argv)
{
	t_game		*game;
	t_player	player;
	t_data		data;
	// mlx_t*		interface;
	game = (t_game *)malloc(sizeof(t_game));
	// start_interface(game, &interface);
	if (argc != 2)
		handle_error(game, "Usage: ./so_long [map.ber]\n", NULL, NULL);
	if (!game)
		handle_error(game, "Failed to allocate memory\n", NULL, NULL);
	init_values(game);
	read_map(argv[1], game);
	validate_map(game, &player, &data);
	free_split(game->map); // Free map array
	free(game); // Free map array
	// mlx_close_window(interface);
	// mlx_terminate(interface);
	return (0);
}
