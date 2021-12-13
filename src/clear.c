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
	game = save_window(NULL);
	mlx_destroy_image(game->mlx, game->img.img);
	mlx_destroy_image(game->mlx, game->player.img);
	mlx_destroy_image(game->mlx, game->item.img);
	mlx_destroy_image(game->mlx, game->wall.img);
	mlx_destroy_image(game->mlx, game->door.img);
	mlx_destroy_window(game->mlx, game->mlx_win);
	clear_array(game->map);
	free(game->mlx);
	exit(0);
	return (0);
}

t_game	*save_window(t_game *game)
{
	static t_game	*win = NULL;

	if (game != NULL)
		win = game;
	return (win);
}
