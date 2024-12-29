#include "so_long.h"

void	start_interface(t_game *game, t_data *data)
{
	mlx_t	*interface;
	int x;
	int y;
	char	**temp;

	interface = mlx_init(WIDTH, HEIGHT, "Recycling Simulator", true);
	if (!interface)
		handle_error(game, "Failed to initialize interface\n", NULL, NULL);
	game->interface = interface;
	load_textures(game);
	x = 0;
	while (x < 1920 / PIXELS)
	{
		y = 0;
		while (y < 1080 / PIXELS)
		{
			if (mlx_image_to_window(interface, game->image.floor, x * PIXELS, y * PIXELS) < 0)
				handle_error(game, "Failed to put game->image.floor to interface\n", NULL, NULL);
			y++;
		}
		x++;
	}
	data->temp_map_x = game->player_x;
	data->temp_map_y = game->player_y;
	temp = create_temp_map(game);
	flood_fill_textures(game, temp, data->temp_map_x, data->temp_map_y);
	free_split(temp);
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

	game = (t_game *)malloc(sizeof(t_game));
	if (argc != 2)
		handle_error(game, "Usage: ./so_long [map.ber]\n", NULL, NULL);
	if (ft_strncmp(ft_strrchr(argv[1], '.'), ".ber", 4) != 0)
		handle_error(game, "Invalid file format\n", NULL, NULL);
	if (!game)
		handle_error(game, "Failed to allocate memory\n", NULL, NULL);
	init_values(game);
	read_map(argv[1], game);
	validate_map(game, &player, &data);
	start_interface(game, &data);
	free_split(game->map);
	free(game);
	return (0);
}
