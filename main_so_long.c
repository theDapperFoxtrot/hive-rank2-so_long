#include "so_long.h"

// void	key_hook()
// {
// }

void	fill_background(t_game *game)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (mlx_image_to_window(game->interface, game->texture.wall,
					x * PIXELS, y * PIXELS) < 0)
				handle_error(game, "Failed to initialize interface\n", NULL, NULL);
			x++;
		}
		y++;
	}
}

void	start_interface(t_game *game)
{
	mlx_t	*interface;

	interface = mlx_init(WIDTH, HEIGHT, "so_long", true);
	if (!(game->interface))
		handle_error(game, "Failed to initialize interface\n", NULL, NULL);
	game->interface = interface;
	fill_background(game);
	// mlx_key_hook(*interface, key_hook, game);
	// mlx_loop_hook(*interface, loop_hook, game);
	mlx_loop(game->interface);
}

int	main(int argc, char **argv)
{
	t_game		*game;
	t_player	player;
	t_data		data;


	game = (t_game *)malloc(sizeof(t_game));
	load_textures(game);
	start_interface(game);
	if (argc != 2)
		handle_error(game, "Usage: ./so_long [map.ber]\n", NULL, NULL);
	if (!game)
		handle_error(game, "Failed to allocate memory\n", NULL, NULL);
	init_values(game);
	read_map(argv[1], game);
	validate_map(game, &player, &data);
	free_split(game->map);
	free(game);
	mlx_close_window(game->interface);
	mlx_terminate(game->interface);
	return (0);
}
