#include "so_long.h"

void	read_map(char *filename, t_game *game)
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
