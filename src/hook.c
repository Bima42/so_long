#include "so_long.h"

int	redraw(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
	return (1);
}

int	press_key(int keycode, t_game *game)
{
	if (keycode == UP || keycode == DOWN || keycode == LEFT
		|| keycode == RIGHT || keycode == W || keycode == S
		|| keycode == A || keycode == D)
		move_player(game, keycode);
	return (keycode);
}
