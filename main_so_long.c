#include "so_long.h"

static void	handle_error(char *message, char **freedom_seekers, char *freedom_seeker)
{
	free(freedom_seeker);
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

static void	*get_next_valid_line(int fd, char *line)
{
	char	*buffer;
	char	*temp;
	int		bytes_read;

	buffer = (char *)malloc(2);
	if (!buffer)
		handle_error("Failed to allocate buffer memory\n", NULL, NULL);
	line = ft_strdup("");
	if (!line)
		handle_error("Failed to allocate line strdup memory\n", NULL, NULL);
	while ((bytes_read = read(fd, buffer, 1)) > 0)
	{
		buffer[1] = '\0';
		if (buffer[0] == '\n')
			break ;
		if (!valid_character(buffer[0]))
		{
			free(buffer);
			handle_error("Invalid character in map\n", NULL, NULL);
		}
		temp = ft_strjoin(line, buffer);
		free(line);
		line = temp;
	}
	free(buffer);
	if (bytes_read == 0)
		return (NULL);
	return (line);
}

char **read_the_map(int fd, int *height, char *line, char **map)
{
	int		i;

	i = 0;
	while (i < (*height) + 1)
	{
		get_next_valid_line(fd, line);
		map[i] = ft_strdup(line);
		free(line);
		i++;
	}
	return (map);
}


static char	**read_map(char *filename, int *width, int *height)
{
	int		fd;
	char	*line;
	char	**map;

	line = ft_calloc(1, sizeof(char) * *width);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		handle_error("Failed to open file\n", NULL, NULL);
	if (!get_next_valid_line(fd, line))
		handle_error("Failed to read file\n", NULL, NULL);
	*width = ft_strlen(line);
	*height = 1;
	while (get_next_valid_line(fd, line))
		(*height)++;
	map = (char **)malloc(sizeof(char *) * *height + 1);
	if (!map)
		handle_error("Failed to allocate memory\n", NULL, NULL);
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		handle_error("Failed to open file\n", NULL, NULL);
	map = read_the_map(fd, height, line, map);
	close(fd);
	return (map);
}

int32_t	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		handle_error("Usage: ./so_long [map.ber]\n", NULL, NULL);
	// Read the map
	game.map = read_map(argv[1], &game.width, &game.height);
	#include <stdio.h>
	int i = 0;
	while (i < game.height + 1)
	{
		printf("%s\n", game.map[i]);
		i++;
	}

	// Parse the map
	// Validate the map
	// Initialize the game


	// mlx_t *mlx;
	// mlx_image_t *image;
	// // Initialize the mlx window
	// mlx = mlx_init(WIDTH, HEIGHT, "so_long", true);
	// if (!mlx)
	// 	handle_error("Failed to initialize mlx\n");
	// // Create a new image
	// image = mlx_new_image(mlx, WIDTH, HEIGHT);
	// if (!image)
	// 	handle_error("Failed to create image\n");
	// // Set a pixel to red (0xFF0000FF = RGBA format: Red)
	// mlx_put_pixel(image, 0, 0, 0xFF0000FF);
	// // Put the image on the window
	// if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	// 	handle_error("Failed to put image on window\n");
	// // Start the event loop
	// mlx_loop(mlx);
	// // Clean up and close
	// mlx_terminate(mlx);
	return (0);
}
