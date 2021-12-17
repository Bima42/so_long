/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 16:21:19 by tpauvret          #+#    #+#             */
/*   Updated: 2021/12/17 17:52:24 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	move_coin_or_empty(t_game *game, t_coord next)
{
	game->map[next.y][next.x] = 'P';
	game->map[game->player_pos.y][game->player_pos.x] = '0';
	game->player_pos.x = next.x;
	game->player_pos.y = next.y;
}

void	move(t_game *game, t_coord next, char *str)
{
	if (is_valid_position(game, next) == 1)
	{
		if (game->map[next.y][next.x] == 'E')
		{
			if (game->coin_count == 0)
				call_end_game(game, str);
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
			move_coin_or_empty(game, next);
			write_move(game, str);
		}
		if (game->map[next.y][next.x] == 'M')
			call_loss_game(game);
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
		game->player = game->player_left;
		move(game, pos, "Move left");
	}
	else if (side == RIGHT || side == A)
	{
		pos.x = game->player_pos.x + 1;
		game->player = game->player_right;
		move(game, pos, "Move right");
	}
	else if (side == UP || side == W
			|| side == DOWN || side == S)
		move_player_2(game, side, pos);
}

void	move_player_2(t_game *game, int side, t_coord pos)
{
	if (side == UP || side == W)
	{
		pos.y = game->player_pos.y - 1;
		game->player = game->player_back;
		move(game, pos, "Move up");
	}
	else if (side == DOWN || side == S)
	{
		pos.y = game->player_pos.y + 1;
		game->player = game->player_front;
		move(game, pos, "Move down");
	}
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
