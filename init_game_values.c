#include "so_long.h"

void	init_values(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	game->map = NULL;
}

void	initial_checks(t_game **game, t_data *data)
{
	*game = (t_game *)malloc(sizeof(t_game));
	if (!(*game))
		handle_error(*game, "Error\nFailed to allocate memory\n", NULL, NULL);
	(*game)->fd = -1;
	if (data->argc != 2)
		handle_error(*game, "Error\nUsage: ./so_long [map.ber]\n", NULL, NULL);
	if (ft_strncmp(ft_strrchr(data->argv[1], '.'), ".ber", 4) != 0)
		handle_error(*game, "Error\nInvalid file format\n", NULL, NULL);
	if ((int) ft_strlen(data->argv[1]) < 5)
		handle_error(*game, "Error\nInvalid map file name\n", NULL, NULL);
	if (access(data->argv[1], F_OK) == -1)
		handle_error(*game, "Error\nThis is not a file\n", NULL, NULL);
}
