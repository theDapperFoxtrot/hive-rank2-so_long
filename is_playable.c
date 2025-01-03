#include "so_long.h"

int	is_playable(t_game *game, t_data *data)
{
	int		result;
	char	**temp;

	data->temp_map_x = game->player_x;
	data->temp_map_y = game->player_y;
	game->collectibles = data->collectibles_count;
	temp = create_temp_map(game);
	if (!temp)
		handle_error(game, "Error\nMemory allocation failed", NULL, NULL);
	result = flood_fill(game, temp, data->temp_map_x, data->temp_map_y);
	if (!result)
	{
		free_split(temp);
		handle_error(game, "Error\nNo valid path available\n", game->map, NULL);
	}
	free_split(temp);
	return (result);
}

char	**create_temp_map(t_game *game)
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

int	flood_fill(t_game *game, \
char **temp_map, int temp_map_x, int temp_map_y)
{
	static int	collectibles = 0;
	static int	exit_found = 0;

	if (temp_map[temp_map_y][temp_map_x] == '1')
		return (0);
	else if (temp_map[temp_map_y][temp_map_x] == 'C')
		collectibles++;
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
	if (collectibles == game->collectibles && exit_found)
		return (1);
	return (0);
}
