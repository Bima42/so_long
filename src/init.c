#include "so_long.h"

void	init_struct(t_game *game, int argc, char **argv)
{
	game->screen_res.x = 0;
	game->screen_res.y = 0;
	game->player_pos.x = 0;
	game->player_pos.y = 0;
	game->coin_count = 0;
	game->move_count = 0;
	game->map = parsing_map(argc, argv, game);
}

void	game_init(t_game *game)
{
	game->mlx = mlx_init();
	create_window(game);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_pixel, &game->img.line_length, &game->img.endian);
	save_window(game);
	set_angle(game);
	texture_load(&game);
	mlx_loop_hook(game->mlx, redraw, game);
	mlx_hook(game->mlx_win, 17, 1L<<0 , exit_game, game);
	mlx_hook(game->mlx_win, 2, 1L<<0, press_key, game);
	mlx_do_key_autorepeaton(game->mlx);
	draw_frame(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
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

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_pixel / 8));
	*(unsigned int*)dst = color;
}

void	set_angle(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	game->map[y][x] = 'A';
	while (game->map[y][x])
		x++;
	game->map[y][--x] = 'A';
	while (y < get_array_size(game->map))
		y++;
	game->map[--y][x] = 'A';
	game->map[y][0] = 'A';
}
