#include "so_long.h"

void	draw_map(t_game *game)
{
//	t_game	game;
//	t_img	map;
	int x = 0, y = 0;;

	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, 920, 480, "so_long");
	game->wall.img = mlx_new_image(game->mlx, 920, 480);
/*	map.addr = mlx_get_data_addr(map.img, &map.bits_pixel, &map.line_length, &map.endian);
	while (x++ < 100)
	{
		y = 0;
		while (y++ < 100)
				my_mlx_pixel_put(&map, x, y, 0x00FF0000);
		my_mlx_pixel_put(&map, x, y, 0x00FF0000);
	}
	mlx_put_image_to_window(game.mlx, game.mlx_win, map.img, 0, 0);*/
	texture_load(game);
	draw_frame(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->wall.img, x, y);
	mlx_loop(game->mlx);
}

void	texture_load(t_game *game)
{
	game->wall.img = mlx_xpm_file_to_image(game->mlx, "./asset/Wall.xpm", &game->wall.width, &game->wall.height);
	game->wall.addr = mlx_get_data_addr(game->wall.img, &game->wall.bits_pixel, &game->wall.line_length, &game->wall.endian);
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

	tex = &game->wall;
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
				my_mlx_pixel_put(&game->wall, (x * 40) + pos.x, (y * 40) + pos.y, color_trans(tex, color));
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
