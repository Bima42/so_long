/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:08:40 by tpauvret          #+#    #+#             */
/*   Updated: 2021/12/17 17:38:45 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	monster_next_move(t_game *game, int next_x)
{
	if (game->map[game->monster_pos.y][next_x] == '1'
		|| game->map[game->monster_pos.y][next_x] == 'E'
		|| game->map[game->monster_pos.y][next_x] == 'C')
		return (0);
	else if (game->map[game->monster_pos.y][next_x] == 'P')
	{
		ft_putstr_fd("							\r", STDOUT_FILENO);
		ft_putstr_fd("You died, avoid the monster !\n", STDOUT_FILENO);
		exit_game(game);
	}
	return (1);
}

void	monster_move_right(t_game *game, int x, int dir, int *flag)
{
	x = game->monster_pos.x + 1;
	if (!monster_next_move(game, x))
		*flag = 1;
	else
	{
		if (dir == 0)
		{
			game->monster = game->monster_side_right;
			dir = 1;
		}
		else
		{
			dir = 0;
			game->monster = game->monster_walk_r;
		}
		game->map[game->monster_pos.y][game->monster_pos.x] = '0';
		game->map[game->monster_pos.y][x] = 'M';
		game->monster_pos.x = x;
	}
}

void	monster_move_left(t_game *game, int x, int dir, int *flag)
{
	x = game->monster_pos.x - 1;
	if (!monster_next_move(game, x))
		*flag = 0;
	else
	{
		if (dir == 0)
		{
			dir = 1;
			game->monster = game->monster_side_left;
		}
		else
		{
			dir = 0;
			game->monster = game->monster_walk_l;
		}
		game->map[game->monster_pos.y][x] = 'M';
		game->map[game->monster_pos.y][game->monster_pos.x] = '0';
		game->monster_pos.x = x;
	}
}	

void	monster_move(t_game *game)
{
	static int	flag = 0;
	static int	dir = 0;
	int			x;

	x = 0;
	if (flag == 0)
		monster_move_right(game, x, dir, &flag);
	else if (flag == 1)
		monster_move_left(game, x, dir, &flag);
}
