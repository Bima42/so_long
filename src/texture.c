/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 14:21:57 by tpauvret          #+#    #+#             */
/*   Updated: 2021/12/17 14:53:52 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	texture_load(t_game **game)
{
	load_one_texture(*game, &(*game)->player, "./asset/player_front.xpm");
	load_one_texture(*game, &(*game)->door, "./asset/door.xpm");
	load_one_texture(*game, &(*game)->item, "./asset/item.xpm");
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

void	load_one_texture(t_game *game, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx,
			path, &tex->width, &tex->height);
	tex->addr = mlx_get_data_addr(tex->img,
			&tex->bits_pixel, &tex->line_length, &tex->endian);
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
	else if (c == '0')
		return (NULL);
	return (NULL);
}
