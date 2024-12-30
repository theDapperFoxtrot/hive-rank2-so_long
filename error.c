#include "so_long.h"

void	handle_error(t_game *game, char *message, \
char **freedom_seekers, char *freedom_seeker)
{
	if (freedom_seeker)
		free(freedom_seeker);
	if (freedom_seekers)
		free_split(freedom_seekers);
	if (game->fd != -1)
		close(game->fd);
	free(game);
	ft_putstr_fd(message, 2);
	exit(1);
}
