#include "so_long.h"

void	clear_array(char **map)
{
	int	i;

	i = 0;
	while (map[i++])
		free(map[i]);
	free(map);
}

int	exit_game(t_game *game)
{
//	mlx_destroy_image(game->mlx, game->img.img);
//	mlx_destroy_image(game->mlx, game->player.img);
//	mlx_destroy_image(game->mlx, game->wall.img);
//	mlx_destroy_image(game->mlx, game->door.img);
//	mlx_destroy_image(game->mlx, game->item.img);
	mlx_destroy_window(game->mlx, game->mlx_win);
//	mlx_destroy_display(game->mlx);
//	mlx_loop_end(game->mlx);
	free(game->mlx);
	exit(0);

	return (0);
}
