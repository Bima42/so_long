/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 14:13:44 by tpauvret          #+#    #+#             */
/*   Updated: 2021/11/22 15:30:27 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	my_mlx_pixel_put(t_map *map, int x, int y, int color)
{
	char	*dst;

	dst = map->addr + (y * map->line_length + x * (map->bits_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(int argc, char **argv)
{
	char	**tab;
	void	*mlx;
	void	*mlx_win;
	t_map	map;

	tab = parsing_map(argc, argv);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Bima");
	map.img = mlx_new_image(mlx, 1920, 1080);
	map.addr = mlx_get_data_addr(map.img, &map.bits_pixel, &map.line_length, &map.endian);
	my_mlx_pixel_put(&map, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, map.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
