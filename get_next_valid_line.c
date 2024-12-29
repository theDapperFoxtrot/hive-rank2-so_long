#include "so_long.h"

int	valid_character(char c)
{
	return (c == '0' || c == '1' || c == 'C' \
	|| c == 'E' || c == 'P' || c == '\0' \
	|| c == '\n' || c == ' ' || c == '\t' \
	|| c == '\v' || c == '\f' || c == '\r');
}

int	read_and_process_buffer(t_game *game, int fd, \
char **line, char *buffer)
{
	char	*temp;
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, 1);
		if (bytes_read < 1)
			break ;
		buffer[1] = '\0';
		if (buffer[0] == '\n' || buffer[0] == '\0')
			break ;
		if (buffer[0] == 32 || buffer[0] == 9 || \
		(buffer[0] > 11 && buffer[0] < 13))
			continue ;
		if (!valid_character(buffer[0]))
		{
			free(buffer);
			handle_error(game, "Error\nInvalid character\n", NULL, *line);
		}
		temp = ft_strjoin(*line, buffer);
		free(*line);
		*line = temp;
	}
	return (bytes_read);
}

void	*get_next_valid_line(t_game *game, int fd, char **line)
{
	char	*buffer;

	buffer = (char *)malloc(2);
	if (!buffer)
		handle_error(game, "Error\nFailed to allocate\n", NULL, NULL);
	read_and_process_buffer(game, fd, line, buffer);
	free(buffer);
	return (*line);
}
