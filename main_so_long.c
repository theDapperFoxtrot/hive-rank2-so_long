#include "so_long.h"
void	render_background(t_game *game)
{
	int x;
	int y;

	x = 0;
	while (x < 1920 / PIXELS)
	{
		y = 0;
		while (y < 1080 / PIXELS)
		{
			if (mlx_image_to_window(game->interface, game->image.floor, x * PIXELS, y * PIXELS) < 0)
				handle_error(game, "Error\nFailed to put game->image.floor to interface\n", NULL, NULL);
			y++;
		}
		x++;
	}
}

void	render_foreground(t_game *game, t_data *data)
{
	char	**temp;

	data->temp_map_x = game->player_x;
	data->temp_map_y = game->player_y;
	temp = create_temp_map(game);
	flood_fill_textures(game, temp, data->temp_map_x, data->temp_map_y);
	free_split(temp);
}

void	start_interface(t_game *game, t_data *data)
{
	mlx_t	*interface;

	interface = mlx_init(WIDTH, HEIGHT, "Recycling Simulator", true);
	if (!interface)
		handle_error(game, "Error\nFailed to initialize interface\n", NULL, NULL);
	game->interface = interface;
	load_textures(game);
	render_background(game);
	render_foreground(game, data);
	mlx_loop(interface);
	// mlx_delete_texture(texture);
	// mlx_key_hook(*interface, key_hook, game);
	// mlx_loop_hook(*interface, loop_hook, game);
}

int	main(int argc, char **argv)
{
	t_game		*game;
	t_player	player;
	t_data		data;

	data.argc = argc;
	data.argv = argv;
	initial_checks(&game, &data);
	init_values(game);
	read_map(argv[1], game);
	validate_map(game, &player, &data);
	start_interface(game, &data);
	free_split(game->map);
	free(game);
	return (0);
}
