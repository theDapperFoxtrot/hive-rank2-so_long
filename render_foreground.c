#include "so_long.h"

void	recall_flood_fill_textures(t_game *game, \
char **temp_map, int temp_map_x, int temp_map_y)
{
	if (temp_map_x + 1 < game->width)
		flood_fill_textures(game, temp_map, temp_map_x + 1, temp_map_y);
	if (temp_map_x - 1 >= 0)
		flood_fill_textures(game, temp_map, temp_map_x - 1, temp_map_y);
	if (temp_map_y + 1 < game->height)
		flood_fill_textures(game, temp_map, temp_map_x, temp_map_y + 1);
	if (temp_map_y - 1 >= 0)
		flood_fill_textures(game, temp_map, temp_map_x, temp_map_y - 1);
}
void	apply_texture(t_game *game, mlx_image_t *texture, int x, int y)
{
	if (mlx_image_to_window(game->interface, texture, x, y) < 0)
		handle_error(game, "Failed to put texture to interface\n", NULL, NULL);
}

int	flood_fill_textures(t_game *game, \
char **temp_map, int temp_map_x, int temp_map_y)
{
	if (temp_map[temp_map_y][temp_map_x] == 'V')
		return (0);
	else if (temp_map[temp_map_y][temp_map_x] == '1')
		apply_texture(game, game->image.wall, temp_map_x * PIXELS, temp_map_y * PIXELS);
	else if (temp_map[temp_map_y][temp_map_x] == 'P')
		apply_texture(game, game->image.player, temp_map_x * PIXELS, temp_map_y * PIXELS);
	else if (temp_map[temp_map_y][temp_map_x] == 'C')
		apply_texture(game, game->image.collectible, temp_map_x * PIXELS, temp_map_y * PIXELS);
	else if (temp_map[temp_map_y][temp_map_x] == 'E')
		apply_texture(game, game->image.exit, temp_map_x * PIXELS, temp_map_y * PIXELS);
	else
		apply_texture(game, game->image.floor, temp_map_x * PIXELS, temp_map_y * PIXELS);
	temp_map[temp_map_y][temp_map_x] = 'V';
	recall_flood_fill_textures(game, temp_map, temp_map_x, temp_map_y);
	if (temp_map_x >= game->width && temp_map_y >= game->height)
		return (1);
	return (0);
}
