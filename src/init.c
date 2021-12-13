#include "so_long.h"

void	game_init(t_game *game)
{
	int x = 0, y = 0;

	game->mlx = mlx_init();
	create_window(game);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_pixel, &game->img.line_length, &game->img.endian);
	texture_load(&game);
//	mlx_hook (game->mlx_win, 33, 1L << 17, exit_game, game);
	mlx_loop_hook(game->mlx, redraw, game);
	mlx_key_hook(game->mlx_win, press_key, game);
	draw_frame(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, x, y);
	mlx_loop(game->mlx);
}

void	create_window(t_game *game)
{
	game->screen_res.x = ft_strlen(*game->map) * 40;
	game->screen_res.y = get_array_size(game->map) * 90;
	game->size = get_size(game->screen_res, game->map);
	game->screen_res.x = game->size * ft_strlen(*game->map);
	game->screen_res.y = game->size * get_array_size(game->map);
	game->mlx_win = mlx_new_window(game->mlx, game->screen_res.x, game->screen_res.y, "so_long");
	game->img.img = mlx_new_image(game->mlx, game->screen_res.x, game->screen_res.y);
}

void	my_mlx_pixel_put(t_img *map, int x, int y, int color)
{
	char	*dst;

	dst = map->addr + (y * map->line_length + x * (map->bits_pixel / 8));
	*(unsigned int*)dst = color;
}
