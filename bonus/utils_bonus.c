/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 13:51:35 by tpauvret          #+#    #+#             */
/*   Updated: 2021/12/17 17:17:19 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	get_size(t_coord res, char **map)
{
	t_coord	size;
	int		len_line;
	int		len_array;

	len_line = ft_strlen(*map);
	len_array = get_array_size(map);
	size.x = res.x / len_line;
	size.y = res.y / len_array;
	if (size.x <= size.y)
	{
		if (size.y * len_line > res.x)
			size.y = res.x - 1;
	}
	else
	{
		if (size.x * len_array > res.y)
			res.x = res.y - 1;
	}
	if (size.x < size.y)
	{
		if (size.x < 1)
			return (1);
		return (size.x);
	}
	return (size.y);
}

int	get_array_size(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	is_valid_position(t_game *game, t_coord next)
{
	int	out;

	out = ((next.x > 0 && next.x < (int)ft_strlen(*game->map))
			&& (next.y > 0 && next.y < (int)get_array_size(game->map)));
	return (out);
}

char	*get_sprite_color(t_img *tex, int x, int y, int size)
{
	int		txt_x;
	int		txt_y;
	char	*color;

	txt_x = 0;
	txt_y = 0;
	txt_x = tex->width / (100 / (((double)x / size) * 100.0));
	txt_y = tex->height / (100 / (((double)y / size) * 100.0));
	color = tex->addr + ((4 * tex->width * txt_y) + (4 * txt_x));
	return (color);
}

void	load_one_texture(t_game *game, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx,
			path, &tex->width, &tex->height);
	tex->addr = mlx_get_data_addr(tex->img,
			&tex->bits_pixel, &tex->line_length, &tex->endian);
}
