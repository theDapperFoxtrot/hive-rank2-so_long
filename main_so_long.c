#include "so_long.h"

void	start_interface(t_game *game, mlx_t **interface)
{
	*interface = mlx_init(WIDTH, HEIGHT, "so_long", true);
	if (!(*interface))
		handle_error(game, "Failed to initialize interface\n", NULL, NULL);
	mlx_loop(*interface);
}

int	main(int argc, char **argv)
{
	t_game		*game;
	t_player	player;
	t_data		data;
	// mlx_t*		interface;
	game = (t_game *)malloc(sizeof(t_game));
	// start_interface(game, &interface);
	if (argc != 2)
		handle_error(game, "Usage: ./so_long [map.ber]\n", NULL, NULL);
	if (!game)
		handle_error(game, "Failed to allocate memory\n", NULL, NULL);
	init_values(game);
	read_map(argv[1], game);
	validate_map(game, &player, &data);
	free_split(game->map); // Free map array
	free(game); // Free map array
	// mlx_close_window(interface);
	// mlx_terminate(interface);
	return (0);
}
