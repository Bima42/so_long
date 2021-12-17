#include "so_long_bonus.h"

void	move(t_game *game, t_coord next, char *str)
{
	if (is_valid_position(game, next) == 1)
	{
		if (game->map[next.y][next.x] == 'E')
		{
			if (game->coin_count == 0)
			{
				write_move(game, str);
				ft_putstr_fd("                            \r", STDOUT_FILENO);
				ft_putstr_fd("You win\n", STDOUT_FILENO);
				exit_game(game);
			}
			else
				ft_putendl_fd(CANT_EXIT, STDOUT_FILENO);
		}
		if (game->map[next.y][next.x] == '0'
			|| game->map[next.y][next.x] == 'C')
		{
			if (game->map[next.y][next.x] == 'C')
			{
				game->map[next.y][next.x] = '0';
				game->coin_count--;
			}
			game->map[next.y][next.x] = 'P';
			game->map[game->player_pos.y][game->player_pos.x] = '0';
			game->player_pos.x = next.x;
			game->player_pos.y = next.y;
			write_move(game, str);
		}
		if (game->map[next.y][next.x] == 'M')
		{
			write_move(game, str);
			ft_putstr_fd("                            \r", STDOUT_FILENO);
			ft_putstr_fd("You loss\n", STDOUT_FILENO);
			exit_game(game);
		}
	}
}

void	move_player(t_game *game, int side)
{
	t_coord	pos;

	pos.x = game->player_pos.x;
	pos.y = game->player_pos.y;
	if (side == LEFT || side == D)
	{
		pos.x = game->player_pos.x - 1;
		game->player = game->player_left;
		move(game, pos, "Move left");
	}
	else if (side == RIGHT || side == A)
	{
		pos.x = game->player_pos.x + 1;
		game->player = game->player_right;
		move(game, pos, "Move right");
	}
	else if (side == UP || side == W)
	{
		pos.y = game->player_pos.y - 1;
		game->player = game->player_back;
		move(game, pos, "Move up");
	}
	else if (side == DOWN || side == S)
	{
		pos.y = game->player_pos.y + 1;
		game->player = game->player_front;
		move(game, pos, "Move down");
	}
}

void	write_move(t_game *game, char *str)
{
	char	*count;

	count = ft_itoa(++game->move_count);
	ft_putstr_fd("                                ", STDOUT_FILENO);
	ft_putstr_fd("\r", STDOUT_FILENO);
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putstr_fd("\r", STDOUT_FILENO);
	draw_frame(game);
	print_move(game);
	redraw(game);
}

int	press_key(int keycode, t_game *game)
{
	if (keycode == ESCAPE)
		exit_game(game);
	if (keycode == UP || keycode == DOWN || keycode == LEFT
		|| keycode == RIGHT || keycode == W || keycode == S
		|| keycode == A || keycode == D)
		move_player(game, keycode);
	return (keycode);
}

void    anim(t_game *game, int *i)
{
	static int	flag = 0;

    if (*i >= 100)
    {
		if (flag == 0)
		{
			game->item = game->item_1;
			flag = 1;
		}
		else if (flag == 1)
		{
			game->item = game->item_2;	
			flag = 2;
		}
		else if (flag == 2)
		{
			game->item = game->item_3;	
			flag = 3;
		}
		else if (flag == 3)
		{
			game->item = game->item_4;	
			flag = 4;
		}
		else if (flag == 4)
		{
			game->item = game->item_5;	
			flag = 0;
		}
        monster_move(game);
        draw_frame(game);
		print_move(game);
        *i = 0;
    }
}

int    monster_next_move(t_game *game, int next_x)
{
    if (game->map[game->monster_pos.y][next_x] == '1'
        || game->map[game->monster_pos.y][next_x] == 'E'
        || game->map[game->monster_pos.y][next_x] == 'C')
        return (0);
    else if (game->map[game->monster_pos.y][next_x] == 'P')
    {
        ft_putstr_fd("                            \r", STDOUT_FILENO);
        ft_putstr_fd("You died, avoid the monster !\n", STDOUT_FILENO);
        exit_game(game);
    }
    return (1);
}

void    monster_move(t_game *game)
{
    static int    flag = 0;
    static int    dir = 0;
    int        x;

    if (flag == 0)
    {
        x = game->monster_pos.x + 1;
        if (!monster_next_move(game, x))
            flag = 1;
        else
        {
			if (dir == 0)
			{
				game->monster = game->monster_side_right;
				dir = 1;
			}
			else
			{
				dir = 0;
				game->monster = game->monster_walk_r;
			}
            game->map[game->monster_pos.y][game->monster_pos.x] = '0';
            game->map[game->monster_pos.y][x] = 'M';
            game->monster_pos.x = x;
        }
    }
    else if (flag == 1)
    {
        x = game->monster_pos.x - 1;
        if (!monster_next_move(game, x))
            flag = 0;
        else
        {
			if (dir == 0)
			{
				dir = 1;
				game->monster = game->monster_side_left;
			}
			else
			{
				dir = 0;
				game->monster = game->monster_walk_l;
			}
            game->map[game->monster_pos.y][x] = 'M';
            game->map[game->monster_pos.y][game->monster_pos.x] = '0';
            game->monster_pos.x = x;
        }
    }
}

void	print_move(t_game *game)
{
	int			color;
	char		*move_count;
	int			x;
    int			y;

    y = 0;
    while (y < 25 && y < game->screen_res.y)
    {
        x = 0;
        while (x < 90 && x < game->screen_res.x)
            my_mlx_pixel_put(&game->img, x++, y, 0xFFFFFF);
        y++;
    }
	move_count = ft_itoa(game->move_count);
	color = 0x000000;
	mlx_string_put(game->mlx, game->mlx_win, 10, 15, color, "Moves: ");
	mlx_string_put(game->mlx, game->mlx_win, 60, 15, color, move_count);
	free(move_count);
}
