#include "so_long.h"

void	start_interface(t_game *game)
{
	mlx_t	*interface;

	interface = mlx_init(WIDTH, HEIGHT, "so_long", true);
	if (!interface)
		handle_error(game, "Failed to initialize interface\n", NULL, NULL);
	game->texture.floor = mlx_load_png(FLOOR);
	if (!game->texture.floor)
		handle_error(game, "Failed to load texture_wall\n", NULL, NULL);
	game->image.floor = mlx_texture_to_image(interface, game->texture.floor);
	if (!game->image.floor)
		handle_error(game, "Failed to convert texture to game->image.floor\n", NULL, NULL);
	int x = 0;
	int y;
	while (x < 40)
	{
		y = 0;
		while (y < 27)
		{
			if (mlx_image_to_window(interface, game->image.floor, x * PIXELS, y * PIXELS) < 0)
				handle_error(game, "Failed to put game->image.floor to interface\n", NULL, NULL);
			y++;
		}
		x++;
	}
	// if (mlx_image_to_window(interface, image_wall, 50, 400) < 0)
	// 	handle_error(game, "Failed to put image_wall to interface\n", NULL, NULL);
	// fill_background(game);
	mlx_loop(interface);
	// mlx_delete_texture(texture);
	// game->interface = interface;
	// fill_background(game);
	// mlx_key_hook(*interface, key_hook, game);
	// mlx_loop_hook(*interface, loop_hook, game);
	// mlx_loop(game->interface);
}

int	main(int argc, char **argv)
{
	t_game		*game;
	t_player	player;
	t_data		data;


	game = (t_game *)malloc(sizeof(t_game));
	// load_textures(game);
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
