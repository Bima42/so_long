/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:10:47 by tpauvret          #+#    #+#             */
/*   Updated: 2021/12/17 17:41:50 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	call_end_game(t_game *game, char *str)
{
	write_move(game, str);
	ft_putstr_fd("								\r", STDOUT_FILENO);
	ft_putstr_fd("You win\n", STDOUT_FILENO);
	exit_game(game);
}

void	call_loss_game(t_game *game)
{
	ft_putstr_fd("								\r", STDOUT_FILENO);
	ft_putstr_fd("You loss\n", STDOUT_FILENO);
	exit_game(game);
}

void	write_move(t_game *game, char *str)
{
//	char	*count;

//	count = ft_itoa(++game->move_count);
	ft_putstr_fd("								", STDOUT_FILENO);
	ft_putstr_fd("\r", STDOUT_FILENO);
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putstr_fd(", count: ", STDOUT_FILENO);
	ft_putnbr_fd(++game->move_count, STDOUT_FILENO);
	ft_putstr_fd("\r", STDOUT_FILENO);
	draw_frame(game);
	print_move(game);
	redraw(game);
}

void	print_move(t_game *game)
{
	int			color;
	char		*move_count;
	int			x;
	int			y;

	y = 0;
	while (y < 25 && y < game->screen_res.y)
	{
		x = 0;
		while (x < 90 && x < game->screen_res.x)
			my_mlx_pixel_put(&game->img, x++, y, 0xFFFFFF);
		y++;
	}
	move_count = ft_itoa(game->move_count);
	color = 0x000000;
	mlx_string_put(game->mlx, game->mlx_win, 10, 15, color, "Moves: ");
	mlx_string_put(game->mlx, game->mlx_win, 60, 15, color, move_count);
	free(move_count);
}
