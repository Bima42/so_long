#include "so_long_bonus.h"

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
//	mlx_destroy_image(game->mlx, game->player_front.img);
//	mlx_destroy_image(game->mlx, game->player_back.img);
//	mlx_destroy_image(game->mlx, game->player_left.img);
//	mlx_destroy_image(game->mlx, game->player_right.img);
	mlx_destroy_image(game->mlx, game->item.img);
//	mlx_destroy_image(game->mlx, game->item_1.img);
//	mlx_destroy_image(game->mlx, game->item_2.img);
//	mlx_destroy_image(game->mlx, game->item_3.img);
//	mlx_destroy_image(game->mlx, game->item_4.img);
//	mlx_destroy_image(game->mlx, game->item_5.img);
	mlx_destroy_image(game->mlx, game->angle_top_left.img);
	mlx_destroy_image(game->mlx, game->angle_top_right.img);
	mlx_destroy_image(game->mlx, game->angle_bot_left.img);
	mlx_destroy_image(game->mlx, game->angle_bot_right.img);
	mlx_destroy_image(game->mlx, game->wall_top.img);
	mlx_destroy_image(game->mlx, game->wall_bot.img);
	mlx_destroy_image(game->mlx, game->wall_right.img);
	mlx_destroy_image(game->mlx, game->wall_left.img);
	mlx_destroy_image(game->mlx, game->monster.img);
//	mlx_destroy_image(game->mlx, game->monster_side_left.img);
//	mlx_destroy_image(game->mlx, game->monster_side_right.img);
//	mlx_destroy_image(game->mlx, game->monster_walk_l.img);
//	mlx_destroy_image(game->mlx, game->monster_walk_r.img);
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
