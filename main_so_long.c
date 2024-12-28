#include "so_long.h"


int	flood_fill_textures(t_game *game, \
char **temp_map, int temp_map_x, int temp_map_y)
{
	static int	collectables = 0;
	static int	exit_found = 0;

	if (temp_map[temp_map_y][temp_map_x] == '1')
	{
		game->texture.wall = mlx_load_png(WALL);
		if (!game->texture.wall)
			handle_error(game, "Failed to load texture_wall\n", NULL, NULL);
		game->image.wall = mlx_texture_to_image(game->interface, game->texture.wall);
		if (!game->image.wall)
			handle_error(game, "Failed to convert texture to game->image.wall\n", NULL, NULL);
		if (mlx_image_to_window(game->interface, game->image.floor, temp_map_x * PIXELS, temp_map_y * PIXELS) < 0)
			handle_error(game, "Failed to put game->image.floor to interface\n", NULL, NULL);
		return (0);
	}
	else if (temp_map[temp_map_y][temp_map_x] == 'C')
	{
		game->texture.collectible = mlx_load_png(COLLECTIBLE);
		if (!game->texture.collectible)
			handle_error(game, "Failed to load texture_collectible\n", NULL, NULL);
		game->image.collectible = mlx_texture_to_image(game->interface, game->texture.collectible);
		if (!game->image.collectible)
			handle_error(game, "Failed to convert texture to game->image.collectible\n", NULL, NULL);
		if (mlx_image_to_window(game->interface, game->image.collectible, temp_map_x * PIXELS, temp_map_y * PIXELS) < 0)
			handle_error(game, "Failed to put game->image.collectible to interface\n", NULL, NULL);
		collectables++;
	}
	else if (temp_map[temp_map_y][temp_map_x] == 'E')
	{
		game->texture.exit = mlx_load_png(EXIT);
		if (!game->texture.exit)
			handle_error(game, "Failed to load texture_exit\n", NULL, NULL);
		game->image.exit = mlx_texture_to_image(game->interface, game->texture.exit);
		if (!game->image.exit)
			handle_error(game, "Failed to convert texture to game->image.exit\n", NULL, NULL);
		if (mlx_image_to_window(game->interface, game->image.exit, temp_map_x * PIXELS, temp_map_y * PIXELS) < 0)
			handle_error(game, "Failed to put game->image.exit to interface\n", NULL, NULL);

		exit_found = 1;
		return (0);
	}
	temp_map[temp_map_y][temp_map_x] = '1';
	flood_fill_textures(game, temp_map, temp_map_x + 1, temp_map_y);
	flood_fill_textures(game, temp_map, temp_map_x - 1, temp_map_y);
	flood_fill_textures(game, temp_map, temp_map_x, temp_map_y + 1);
	flood_fill_textures(game, temp_map, temp_map_x, temp_map_y - 1);
	if (collectables == game->collectables && exit_found)
		return (1);
	return (0);
}

void	start_interface(t_game *game/*, t_data *data*/)
{
	mlx_t	*interface;
	// char	**temp;

	interface = mlx_init(WIDTH, HEIGHT, "so_long", true);
	if (!interface)
		handle_error(game, "Failed to initialize interface\n", NULL, NULL);
	game->interface = interface;
	load_textures(game);
	int x = 0;
	int y;
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
	// data->temp_map_x = game->player_x;
	// data->temp_map_y = game->player_y;
	// temp = create_temp_map(game);
	// flood_fill_textures(game, temp, data->temp_map_x, data->temp_map_y);
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
	start_interface(game/*, &data*/);
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
