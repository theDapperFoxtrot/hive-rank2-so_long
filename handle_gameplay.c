#include "so_long.h"

void	reapply_textures_count_steps(t_game *game, int x, int y)
{
	int		px;
	int		py;

	px = game->player_x;
	py = game->player_y;
	if (game->map[y][x] == 'E')
		return ;
	game->map[py][px] = '0';
	game->map[y][x] = 'P';
	apply_texture(game, game->image.floor, px * PIXELS, py * PIXELS);
	apply_texture(game, game->image.player, x * PIXELS, y * PIXELS);
	if (!game->bottles_returned)
	{
		ft_putstr_fd("👟 Steps: ", 1);
		ft_putstr_fd(ft_itoa(game->steps), 1);
		ft_putstr_fd("\n\n", 1);
	}
}

void	collect_trash(t_game *game, int x, int y)
{
	static int	collectibles = 0;

	apply_texture(game, game->image.floor, x * PIXELS, y * PIXELS);
	if (collectibles < game->collectibles)
	{
		ft_putstr_fd("You collected a bottle! ", 1);
		game->score = game->score + 15;
		ft_putstr_fd("💶 That's €0.15!\n\n", 1);
		collectibles++;
	}
	if (collectibles == game->collectibles)
	{
		ft_putstr_fd("🧹 You collected all the trash!\n", 1);
		ft_putstr_fd("🤑 Head for the bottle return station!\n\n", 1);
		game->over = 1;
	}
}

void	game_over_check(t_game *game)
{
	if (game->over)
	{
		ft_putstr_fd("\n\n🏆 You did it!\n", 1);
		ft_putstr_fd("👛 You earned: ", 1);
		ft_putstr_fd(ft_itoa(15 * game->collectibles), 1);
		ft_putstr_fd(" cents!\n", 1);
		ft_putstr_fd("🙏 Thanks for playing!\n", 1);
		ft_putstr_fd("Press the ESC key to exit...", 1);
		game->bottles_returned = 1;
	}
	else
		ft_putstr_fd(\
		"You're just going to leave trash on the ground? 💰\n\n", 1);
}

void	move_player(t_game *game, int x, int y)
{
	if (game->map[y][x] == '1')
		return ;
	if (game->map[y][x] == 'E')
	{
		reapply_textures_count_steps(game, x, y);
		game_over_check(game);
		return ;
	}
	if (game->map[y][x] == '0')
		reapply_textures_count_steps(game, x, y);
	else if (game->map[y][x] == 'C')
	{
		collect_trash(game, x, y);
		reapply_textures_count_steps(game, x, y);
	}
	game->player_x = x;
	game->player_y = y;
	game->steps++;
}

void	key_hooks(mlx_key_data_t data, void *param)
{
	t_game	*game;
	int		x;
	int		y;

	game = (t_game *)param;
	x = game->player_x;
	y = game->player_y;
	if (data.key == MLX_KEY_ESCAPE && data.action == MLX_RELEASE)
		mlx_close_window(game->interface);
	else if ((data.key == MLX_KEY_UP && data.action == MLX_PRESS)
		|| (data.key == MLX_KEY_W && data.action == MLX_PRESS))
		move_player(game, x, y - 1);
	else if ((data.key == MLX_KEY_DOWN && data.action == MLX_PRESS)
		|| (data.key == MLX_KEY_S && data.action == MLX_PRESS))
		move_player(game, x, y + 1);
	else if ((data.key == MLX_KEY_LEFT && data.action == MLX_PRESS)
		|| (data.key == MLX_KEY_A && data.action == MLX_PRESS))
		move_player(game, x - 1, y);
	else if ((data.key == MLX_KEY_RIGHT && data.action == MLX_PRESS)
		|| (data.key == MLX_KEY_D && data.action == MLX_PRESS))
		move_player(game, x + 1, y);
}
