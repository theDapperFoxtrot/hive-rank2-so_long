#include "so_long.h"

mlx_image_t	*load_image(t_game *game, const char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	image = NULL;
	texture = mlx_load_png(path);
	if (!texture)
		handle_error(game, "Failed to load texture\n", NULL, NULL);
	image = mlx_texture_to_image(game->interface, texture);
	if (!image)
		handle_error(game, "Failed to convert texture to image\n", NULL, NULL);
	mlx_delete_texture(texture);
	return (image);
}

void	load_textures(t_game *game)
{
	game->image.wall = load_image(game, WALL);
	game->image.floor = load_image(game, FLOOR);
	game->image.player = load_image(game, PLAYER);
	game->image.collectible = load_image(game, COLLECTIBLE);
	game->image.exit = load_image(game, WALL);
}
