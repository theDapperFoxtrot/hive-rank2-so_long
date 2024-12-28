#include "so_long.h"

int	flood_fill_textures(t_game *game, \
char **temp_map, int temp_map_x, int temp_map_y)
{
	static int	collectables = 0;
	static int	exit_found = 0;

	if (temp_map[temp_map_y][temp_map_x] == 'V')
		return (0);
	else if (temp_map[temp_map_y][temp_map_x] == '1')
	{
		if (mlx_image_to_window(game->interface, game->image.wall, temp_map_x * PIXELS, temp_map_y * PIXELS) < 0)
			handle_error(game, "Failed to put game->image.wall to interface\n", NULL, NULL);
	}
	else if (temp_map[temp_map_y][temp_map_x] == 'P')
	{
		if (mlx_image_to_window(game->interface, game->image.player, temp_map_x * PIXELS, temp_map_y * PIXELS) < 0)
			handle_error(game, "Failed to put game->image.player to interface\n", NULL, NULL);
	}
	else if (temp_map[temp_map_y][temp_map_x] == 'C')
	{
		if (mlx_image_to_window(game->interface, game->image.collectible, temp_map_x * PIXELS, temp_map_y * PIXELS) < 0)
			handle_error(game, "Failed to put game->image.collectible to interface\n", NULL, NULL);
		collectables++;
	}
	else if (temp_map[temp_map_y][temp_map_x] == 'E')
	{
		if (mlx_image_to_window(game->interface, game->image.exit, temp_map_x * PIXELS, temp_map_y * PIXELS) < 0)
			handle_error(game, "Failed to put game->image.exit to interface\n", NULL, NULL);
		exit_found = 1;
	}
	temp_map[temp_map_y][temp_map_x] = 'V';
	// Check bounds before recursive calls
	if (temp_map_x + 1 < game->width)
		flood_fill_textures(game, temp_map, temp_map_x + 1, temp_map_y);
	if (temp_map_x - 1 >= 0)
		flood_fill_textures(game, temp_map, temp_map_x - 1, temp_map_y);
	if (temp_map_y + 1 < game->height)
		flood_fill_textures(game, temp_map, temp_map_x, temp_map_y + 1);
	if (temp_map_y - 1 >= 0)
		flood_fill_textures(game, temp_map, temp_map_x, temp_map_y - 1);
	if (collectables == game->collectables && exit_found)
		return (1);
	return (0);
}

void	start_interface(t_game *game, t_data *data)
{
	mlx_t	*interface;
	int x;
	int y;
	char	**temp;

	interface = mlx_init(WIDTH, HEIGHT, "so_long", true);
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
