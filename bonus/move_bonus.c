#include "so_long_bonus.h"

void	move(t_game *game, t_coord next, char *str)
{
	if (is_valid_position(game, next) == 1)
	{
		if (game->map[next.y][next.x] == 'E')
		{
			if (game->coin_count == 0)
			{
				write_move(game, str);
				ft_putstr_fd("                            \r", STDOUT_FILENO);
				ft_putstr_fd("You win\n", STDOUT_FILENO);
				exit_game(game);
			}
			else
				ft_putendl_fd(CANT_EXIT, STDOUT_FILENO);
		}
		if (game->map[next.y][next.x] == '0'
			|| game->map[next.y][next.x] == 'C')
		{
			if (game->map[next.y][next.x] == 'C')
			{
				game->map[next.y][next.x] = '0';
				game->coin_count--;
			}
			game->map[next.y][next.x] = 'P';
			game->map[game->player_pos.y][game->player_pos.x] = '0';
			game->player_pos.x = next.x;
			game->player_pos.y = next.y;
			write_move(game, str);
		}
	}
}

void	move_player(t_game *game, int side)
{
	t_coord	pos;

	pos.x = game->player_pos.x;
	pos.y = game->player_pos.y;
	if (side == LEFT || side == D)
	{
		pos.x = game->player_pos.x - 1;
		move(game, pos, "Move left");
	}
	else if (side == RIGHT || side == A)
	{
		pos.x = game->player_pos.x + 1;
		move(game, pos, "Move right");
	}
	else if (side == UP || side == W)
	{
		pos.y = game->player_pos.y - 1;
		move(game, pos, "Move up");
	}
	else if (side == DOWN || side == S)
	{
		pos.y = game->player_pos.y + 1;
		move(game, pos, "Move down");
	}
}

void	write_move(t_game *game, char *str)
{
	ft_putstr_fd("                                ", STDOUT_FILENO);
	ft_putstr_fd("\r", STDOUT_FILENO);
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putstr_fd(", count: ", STDOUT_FILENO);
	ft_putnbr_fd(++game->move_count, STDOUT_FILENO);
	ft_putstr_fd("\r", STDOUT_FILENO);
	draw_frame(game);
	redraw(game);
}

int	press_key(int keycode, t_game *game)
{
	if (keycode == ESCAPE)
		exit_game(game);
	if (keycode == UP || keycode == DOWN || keycode == LEFT
		|| keycode == RIGHT || keycode == W || keycode == S
		|| keycode == A || keycode == D)
		move_player(game, keycode);
	return (keycode);
}
