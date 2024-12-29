#include "so_long.h"

void	validate_map(t_game *game, t_player *player, t_data *data)
{
	char	*current_line;
	char	*next_line;
	int		i;

	i = 0;
	if (game->height < 4 || game->width < 4)
		handle_error(game, "Error\nMap is too small\n", game->map, NULL);
	while (game->map[i])
	{
		current_line = game->map[i];
		next_line = (game->map[i + 1]);
		if ((int) ft_strlen(current_line) != game->width)
			handle_error(game, "Error\nMap is not rectangular\n", game->map, NULL);
		if (next_line == NULL)
			break ;
		i++;
	}
	necessary_characters(game, player, data);
	check_walls(game);
	is_playable(game, player, data);
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
