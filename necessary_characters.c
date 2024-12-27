#include "so_long.h"

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
