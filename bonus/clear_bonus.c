/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 13:50:46 by tpauvret          #+#    #+#             */
/*   Updated: 2021/12/17 16:14:30 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	clear_array(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

int	exit_game(t_game *game)
{
	game = save_window(NULL);
	mlx_destroy_image(game->mlx, game->img.img);
	mlx_destroy_image(game->mlx, game->player.img);
	mlx_destroy_image(game->mlx, game->item.img);
	mlx_destroy_image(game->mlx, game->angle_top_left.img);
	mlx_destroy_image(game->mlx, game->angle_top_right.img);
	mlx_destroy_image(game->mlx, game->angle_bot_left.img);
	mlx_destroy_image(game->mlx, game->angle_bot_right.img);
	mlx_destroy_image(game->mlx, game->wall_top.img);
	mlx_destroy_image(game->mlx, game->wall_bot.img);
	mlx_destroy_image(game->mlx, game->wall_right.img);
	mlx_destroy_image(game->mlx, game->wall_left.img);
	mlx_destroy_image(game->mlx, game->monster.img);
	mlx_destroy_image(game->mlx, game->door.img);
	mlx_destroy_window(game->mlx, game->mlx_win);
	clear_array(game->map);
	free(game->mlx);
	exit(0);
	return (0);
}

t_game	*save_window(t_game *game)
{
	static t_game	*win = NULL;

	if (game != NULL)
		win = game;
	return (win);
}
