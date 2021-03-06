/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 13:51:30 by tpauvret          #+#    #+#             */
/*   Updated: 2021/12/17 17:17:25 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	texture_load(t_game **game)
{
	load_one_texture(*game, &(*game)->monster,
		"./asset/monster_front.xpm");
	load_one_texture(*game, &(*game)->monster_side_left,
		"./asset/monster_side_left.xpm");
	load_one_texture(*game, &(*game)->monster_side_right,
		"./asset/monster_side_right.xpm");
	load_one_texture(*game, &(*game)->monster_walk_l,
		"./asset/monster_walk_l.xpm");
	load_one_texture(*game, &(*game)->monster_walk_r,
		"./asset/monster_walk_r.xpm");
	load_one_texture(*game, &(*game)->player,
		"./asset/player_front.xpm");
	load_one_texture(*game, &(*game)->player_front, "./asset/player_front.xpm");
	load_one_texture(*game, &(*game)->player_back, "./asset/player_back.xpm");
	load_one_texture(*game, &(*game)->player_left, "./asset/player_left.xpm");
	load_one_texture(*game, &(*game)->player_right, "./asset/player_right.xpm");
	load_one_texture(*game, &(*game)->door, "./asset/door.xpm");
	load_one_texture(*game, &(*game)->item, "./asset/item_5.xpm");
	load_one_texture(*game, &(*game)->item_1, "./asset/item_1.xpm");
	load_one_texture(*game, &(*game)->item_2, "./asset/item_2.xpm");
	load_one_texture(*game, &(*game)->item_3, "./asset/item_3.xpm");
	load_one_texture(*game, &(*game)->item_4, "./asset/item_4.xpm");
	load_one_texture(*game, &(*game)->item_5, "./asset/item_5.xpm");
	texture_load_2(game);
}

void	texture_load_2(t_game **game)
{
	load_one_texture(*game, &(*game)->wall_top, "./asset/wall_top.xpm");
	load_one_texture(*game, &(*game)->wall_bot, "./asset/wall_bot.xpm");
	load_one_texture(*game, &(*game)->wall_left, "./asset/wall_left.xpm");
	load_one_texture(*game, &(*game)->wall_right, "./asset/wall_right.xpm");
	load_one_texture(*game, &(*game)->angle_top_left,
		"./asset/angle_top_left.xpm");
	load_one_texture(*game, &(*game)->angle_top_right,
		"./asset/angle_top_right.xpm");
	load_one_texture(*game, &(*game)->angle_bot_left,
		"./asset/angle_bot_left.xpm");
	load_one_texture(*game, &(*game)->angle_bot_right,
		"./asset/angle_bot_right.xpm");
}

t_img	*choose_texture_angle(t_game *game, int x, int y)
{
	if (y == 0 && x == 0)
		return (&game->angle_top_left);
	else if (y == 0 && x != 0)
		return (&game->angle_top_right);
	else if (y != 0 && x == 0)
		return (&game->angle_bot_left);
	else if (y != 0 && x != 0)
		return (&game->angle_bot_right);
	return (NULL);
}

t_img	*choose_texture_wall(t_game *game, int x, int y, int max_x)
{
	if (y == 0)
		return (&game->wall_top);
	else if (y != 0 && y != game->nb_lines && x == 0)
		return (&game->wall_left);
	else if (y != 0 && x == max_x)
		return (&game->wall_right);
	else if (y == game->nb_lines && x != 0)
		return (&game->wall_bot);
	else
		return (&game->wall_top);
	return (NULL);
}

t_img	*texture_choice(t_game *game, char c, int y, int x)
{
	int	max_x;

	max_x = 0;
	while (game->map[y][max_x])
		max_x++;
	max_x--;
	if (c == 'P')
		return (&game->player);
	else if (c == '1')
		return (choose_texture_wall(game, x, y, max_x));
	else if (c == 'A')
		return (choose_texture_angle(game, x, y));
	else if (c == 'E')
		return (&game->door);
	else if (c == 'C')
		return (&game->item);
	else if (c == 'M')
		return (&game->monster);
	else if (c == '0')
		return (NULL);
	return (NULL);
}
