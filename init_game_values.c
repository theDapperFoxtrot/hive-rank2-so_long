#include "so_long.h"

void	init_values(t_game *game)
{
	game->map = NULL;
	game->width = 0;
	game->height = 0;
	game->collectables = 0;
	game->exit_x = 0;
	game->exit_y = 0;
}
