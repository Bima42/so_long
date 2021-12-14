#include "so_long.h"

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

int    my_mlx_pixel_get(t_img t, int x, int y)
{
    int    color;
    int    *int_addr;

    int_addr = (int *)t.addr;
    color = int_addr[y * t.width + (x * t.width)];
    return (color);
}

int	redraw(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
	return (1);
}

