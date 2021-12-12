#include "so_long.h"

void	draw_map(t_game *game)
{
	int x = 0, y = 0;;

	game->mlx = mlx_init();
	create_window(game);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_pixel, &game->img.line_length, &game->img.endian);
	texture_load(&game);
	draw_frame(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, x, y);
	mlx_loop(game->mlx);
}

void	create_window(t_game *game)
{
//	mlx_get_screen_size(game->mlx, &game->screen_res.x, &game->screen_res.y);
	game->screen_res.x = ft_strlen(*game->map) * 40;
	game->screen_res.y = get_array_size(game->map) * 90;
	game->size = get_size(game->screen_res, game->map);
	game->screen_res.x = game->size * ft_strlen(*game->map);
	game->screen_res.y = game->size * get_array_size(game->map);
	game->mlx_win = mlx_new_window(game->mlx, game->screen_res.x, game->screen_res.y, "so_long");
	game->img.img = mlx_new_image(game->mlx, game->screen_res.x, game->screen_res.y);
}

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

void	texture_load(t_game **game)
{
	load_one_texture(*game, &(*game)->player, "./asset/player.xpm");
	load_one_texture(*game, &(*game)->wall, "./asset/wall.xpm");
	load_one_texture(*game, &(*game)->door, "./asset/door.xpm");
	load_one_texture(*game, &(*game)->item, "./asset/item.xpm");
}

void	load_one_texture(t_game *game, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, path, &tex->width, &tex->height);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_pixel, &tex->line_length, &tex->endian);
}

char    *get_sprite_color(t_img *tex, int x, int y, int cubesize)
{
    int        txt_x;
    int        txt_y;
    char    *color;

    txt_x = 0;
    txt_y = 0;
    txt_x = tex->width / (100 / (((double)x / cubesize) * 100.0));
    txt_y = tex->height / (100 / (((double)y / cubesize) * 100.0));
    color = tex->addr + ((4 * tex->width * txt_y) + (4 * txt_x));
    return (color);
}

int    my_mlx_pixel_get(t_img t, int x, int y)
{
    int    color;
    int    *int_addr;

    int_addr = (int *)t.addr;
    color = int_addr[y * t.width + (x * t.width)];
    return (color);
}

void	draw(t_game *game, int x, int y)
{
	t_coord	pos;
	char	*color;
	t_img	*tex;

	tex = texture_choice(game, game->map[y][x]);
	pos.y = 0;
	while (pos.y < 40)
	{
		pos.x = 0;
		while (pos.x < 40)
		{
			color = "";
			if (tex)
				color = get_sprite_color(tex, pos.x, pos.y, 40);
			if (color != NULL)
				my_mlx_pixel_put(&game->img, (x * 40) + pos.x, (y * 40) + pos.y, color_trans(tex, color));
			pos.x++;
		}
		pos.y++;
	}
}

int    color_trans(t_img *tex, char *color)
{
    int        transparancy;
    int        actual;
    int        background;

    background = 0xFFFFFF;
    if (!tex)
        return (background);
    transparancy = my_mlx_pixel_get(*tex, 0, 0);
    actual = *(int *)color;
    if (actual == transparancy)
        return (background);
    else
        return (actual);
} 

void	draw_frame(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (game->map[y])
	{
		while (game->map[y][x])
		{
			draw(game, x, y);
			x++;
		}
		x = 0;
		y++;
	}
}

t_img	*texture_choice(t_game *game, char c)
{
	if (c == 'P')
		return (&game->player);
	else if (c == '1')
		return (&game->wall);
	else if (c == 'E')
		return (&game->door);
	else if (c == 'C')
		return (&game->item);
	else if (c == '0')
		return (NULL);
	return (NULL);
}
