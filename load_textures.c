#include "so_long.h"

mlx_image_t	*load_image(t_game *game, const char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	image = NULL;
	texture = mlx_load_png(path);
	if (!texture)
	{
		mlx_terminate(game->interface);
		handle_error(game, "Error\nFailed to load texture\n", game->map, NULL);
	}
	image = mlx_texture_to_image(game->interface, texture);
	if (!image)
	{
		mlx_delete_texture(texture);
		mlx_terminate(game->interface);
		handle_error(game, \
		"Error\nFailed to convert texture to image\n", game->map, NULL);
	}
	mlx_delete_texture(texture);
	return (image);
}

void	load_textures(t_game *game)
{
	game->image.wall = load_image(game, WALL);
	game->image.floor = load_image(game, FLOOR);
	game->image.player = load_image(game, PLAYER);
	game->image.collectible = load_image(game, COLLECTIBLE);
	game->image.exit = load_image(game, EXIT);
}
