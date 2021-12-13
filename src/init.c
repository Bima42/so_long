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
