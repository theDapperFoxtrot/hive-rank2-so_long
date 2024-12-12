#include "so_long.h"



	#include <stdio.h>


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
	*line = ft_strdup("");
	if (!*line)
		handle_error("Failed to allocate *line strdup memory\n", NULL, NULL);
	while ((bytes_read = read(fd, buffer, 1)) > 0)
	{
		if (bytes_read)
		buffer[1] = '\0';
		if (buffer[0] == '\n' || buffer[0] == '\0')
			break ;
		if (!valid_character(buffer[0]))
		{
			free(buffer);
			handle_error("Invalid character in map\n", NULL, NULL);
		}
		temp = ft_strjoin(*line, buffer);
		free(*line);
		*line = temp;
	}
	free(buffer);
	return (*line);
}

static char	**read_map(char *filename, int *width, int *height)
{
	int		fd;
	char	*line;
	char	**map;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		handle_error("Failed to open file\n", NULL, NULL);
	line = NULL;
	*height = 0;
	while (get_next_valid_line(fd, &line) && *line)
	{
		if (*height == 0)
			*width = ft_strlen(line);
		(*height)++;
		free(line);
	}
	printf("height: %d\n", *height);
	close(fd);
	// Allocate memory for the map
	map = (char **)malloc(sizeof(char *) * (*height));
	if (!map)
		handle_error("Failed to allocate memory\n", NULL, NULL);
	// Reopen file to populate map
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
			free_split(map); // Clean up allocated rows
			handle_error("Failed to allocate memory for map\n", NULL, line);
		}
		free(line);
		i++;
	}
	map[i] = NULL; // Null-terminate map
	close(fd);
	return (map);
}

int32_t	main(int argc, char **argv)
{
	t_game	game;
	int		i;

	if (argc != 2)
		handle_error("Usage: ./so_long [map.ber]\n", NULL, NULL);
	// Read the map
	game.map = read_map(argv[1], &game.width, &game.height);
	i = 0;
	while (i < game.height)
	{
		printf("%s\n", game.map[i]);
		i++;
	}
	free_split(game.map); // Free map array
	return (0);
}
