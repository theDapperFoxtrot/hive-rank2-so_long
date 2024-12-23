#include "so_long.h"

	// #include <stdio.h>
	// #include <string.h>

static void	handle_error(char *message, char **freedom_seekers, char *freedom_seeker)
{
	if (freedom_seeker)
		free(freedom_seeker);
	if (freedom_seekers)
		free_split(freedom_seekers);
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

static void	*get_next_valid_line(int fd, char **line)
{
	char	*buffer;
	char	*temp;
	int		bytes_read;

	buffer = (char *)malloc(2);
	if (!buffer)
		handle_error("Failed to allocate buffer memory\n", NULL, NULL);
	while ((bytes_read = read(fd, buffer, 1)) > 0)
	{
		if (bytes_read)
		buffer[1] = '\0';
		if (buffer[0] == '\n' || buffer[0] == '\0')
			break ;
		if (!valid_character(buffer[0]))
		{
			free(buffer);
			handle_error("Invalid character in map\n", NULL, *line);
		}
		temp = ft_strjoin(*line, buffer);
		free(*line);
		*line = temp;
	}
	free(buffer);
	return (*line);
}

static char **read_map(char *filename, int *width, int *height)
{
    int fd;
    char *line;
    char **map;
    int i;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        handle_error("Failed to open file\n", NULL, NULL);
    line = NULL;
    *height = 0;
    *width = 0;
    while (get_next_valid_line(fd, &line) && *line)
    {
        if (*height == 0)
            *width = ft_strlen(line);
        (*height)++;
        free(line);
        line = NULL;
    }
    close(fd);
    map = (char **)malloc(sizeof(char *) * (*height + 1));
    if (!map)
        handle_error("Failed to allocate memory\n", NULL, NULL);
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        handle_error("Failed to open file\n", map, NULL);
    i = 0;
    while (i < *height)
    {
        get_next_valid_line(fd, &line);
        map[i] = ft_strdup(line);
        if (!map[i])
        {
            free_split(map);
            handle_error("Failed to allocate memory for map\n", NULL, line);
        }
        free(line);
        line = NULL;
        i++;
    }
	map[i] = NULL;
    close(fd);
    return (map);
}

void	necessary_characters(char **map, int width, int height)
{
	int		i;
	int		j;
	int		player;
	int		exit;
	int		collectible;

	i = 0;
	player = 0;
	exit = 0;
	collectible = 0;
	while (i < height)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
				player++;
			else if (map[i][j] == 'E')
				exit++;
			else if (map[i][j] == 'C')
				collectible++;
			j++;
		}
		i++;
	}
	if (player != 1 || exit != 1 || collectible < 1)
		handle_error("Map is missing necessary characters\n", map, NULL);
}

void	validate_map(char **map, int width, int height)
{
	char *current_line;
	char *next_line;

	if (height < 4 || width < 4)
		handle_error("Map is too small\n", map, NULL);
	while (*map)
	{
		current_line = *map;
		next_line = *(map + 1);
		if (next_line == NULL)
			break ;
		if (ft_strlen(current_line) != width)
			handle_error("Map is not rectangular\n", map, NULL);
		map++;
	}
	necessary_characters(map, width, height);
}

int	main(int argc, char **argv)
{
	t_game	game;
	// int		i;
	// int		j;

	if (argc != 2)
		handle_error("Usage: ./so_long [map.ber]\n", NULL, NULL);
	// Read the map
	game.map = read_map(argv[1], &game.width, &game.height);
	validate_map(game.map, game.width, game.height);
	// i = 0;
	// while (i < game.height)
	// {
	// 	j = 0;
	// 	while (game.map[i][j])
	// 	{
	// 		printf("bytes[%d]: %ld byte(s)\n", j, sizeof(game.map[i][j]));
	// 		j++;
	// 	}
	// 	printf("line: %s\nsize of line#:%ld bytes\n", game.map[i], sizeof(game.map[i]));
	// 	i++;
	// }
	// printf("line: %s\nsize of line#:%ld bytes\n", game.map[i], sizeof(game.map[i]));
	free_split(game.map); // Free map array
	return (0);
}
