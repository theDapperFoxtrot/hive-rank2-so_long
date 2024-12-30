#include "so_long.h"

void	start_interface(t_game *game, t_data *data)
{
	mlx_t	*interface;

	interface = mlx_init(game->width * PIXELS, \
	game->height * PIXELS, "Recycling Simulator", true);
	if (!interface)
		handle_error(game, \
		"Error\nFailed to initialize interface\n", NULL, NULL);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	game->interface = interface;
	load_textures(game);
	render_background(game);
	render_foreground(game, data);
	mlx_key_hook(game->interface, &key_hooks, game);
	mlx_loop(game->interface);
	mlx_terminate(game->interface);
}

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
	// start_interface(game, &data);
	free_split(game->map);
	free(game);
	return (0);
}
