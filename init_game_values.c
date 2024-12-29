#include "so_long.h"

void	init_values(t_game *game)
{
	game->map = NULL;
	game->width = 0;
	game->height = 0;
	game->collectibles = 0;
	game->exit_x = 0;
	game->exit_y = 0;
	game->player_x = 0;
	game->player_y = 0;
	game->score = 0;
	game->steps = 0;
	game->over = 0;
	game->bottles_returned = 0;
}

void	initial_checks(t_game **game, t_data *data)
{
	*game = (t_game *)malloc(sizeof(t_game));
	if (!(*game))
		handle_error(*game, "Error\nFailed to allocate memory\n", NULL, NULL);
	if (data->argc != 2)
		handle_error(*game, "Error\nUsage: ./so_long [map.ber]\n", NULL, NULL);
	if (ft_strncmp(ft_strrchr(data->argv[1], '.'), ".ber", 4) != 0)
		handle_error(*game, "Error\nInvalid file format\n", NULL, NULL);
}
