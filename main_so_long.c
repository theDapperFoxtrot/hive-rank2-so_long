#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game		*game;
	t_data		data;

	data.argc = argc;
	data.argv = argv;
	initial_checks(&game, &data);
	init_values(game);
	read_map(argv[1], game);
	validate_map(game, &data);
	start_interface(game, &data);
	free_split(game->map);
	free(game);
	return (0);
}
