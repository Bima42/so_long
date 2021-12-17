/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:12:21 by tpauvret          #+#    #+#             */
/*   Updated: 2021/12/17 17:13:11 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	anim_coin(t_game *game, int *flag)
{
	if (*flag == 0)
	{
		game->item = game->item_1;
		*flag = 1;
	}
	else if (*flag == 1)
	{
		game->item = game->item_2;
		*flag = 2;
	}
	else if (*flag == 2)
	{
		game->item = game->item_3;
		*flag = 3;
	}
	else if (*flag == 3)
	{
		game->item = game->item_4;
		*flag = 4;
	}
	else if (*flag == 4)
	{
		game->item = game->item_5;
		*flag = 0;
	}
}

void	anim(t_game *game, int *i)
{
	static int	flag = 0;

	if (*i >= 10)
	{
		anim_coin(game, &flag);
		monster_move(game);
		draw_frame(game);
		print_move(game);
		*i = 0;
	}
}
