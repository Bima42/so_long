/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 14:13:55 by tpauvret          #+#    #+#             */
/*   Updated: 2021/12/09 15:51:46 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# define BUFFER_SIZE 10

# define ESCAPE 53
# define UP 126
# define DOWN 125
# define RIGHT 124
# define LEFT 123
# define Z 6
# define Q 12
# define S 1
# define D 0
# define W 13
# define A 2
# define CANT_EXIT "Can't exit because you don't collect all coins"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "mlx.h"
#include "get_next_line/get_next_line.h"
#include "libft.h"

typedef struct	s_map
{
	int	empty;
	int	wall;
	int	coin;
	int	exit;
	int	pos;
	int	nb_lines;
}				t_map;

typedef struct	s_coord
{
	int	x;
	int	y;
}				t_coord;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_pixel;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}				t_img;

typedef struct	s_game
{
	char		**map;
	void		*mlx;
	void		*mlx_win;
	int			nb_lines;
	int			size;
	int			coin_count;
	int			move_count;
	t_coord		screen_res;
	t_coord		player_pos;
	t_coord		monster_pos;
	t_img		img;
	t_img	angle_top_left;
	t_img	angle_top_right;
	t_img	angle_bot_left;
	t_img	angle_bot_right;
	t_img	wall_top;
	t_img	wall_bot;
	t_img	wall_right;
	t_img	wall_left;
	t_img	player;
	t_img	player_front;
	t_img	player_back;
	t_img	player_left;
	t_img	player_right;
	t_img	monster;
	t_img	monster_side_left;
	t_img	monster_side_right;
	t_img	monster_walk_l;
	t_img	monster_walk_r;
	t_img	door;
	t_img	item;
	t_img	item_1;
	t_img	item_2;
	t_img	item_3;
	t_img	item_4;
	t_img	item_5;
}				t_game;

//Parsing_map
char	**parsing_map(int argc, char **argv, t_game *game);
void	check_wall(char **map, t_map data);
void	check_wall_2(char **map, t_map data);
void	check_wall_3(char **map, size_t len);
void	write_error(char **map);

//Check_error
void	init(t_map *map, int lines);
void	set_data(char *line, t_map *data, t_game *game);
char	*get_line(int fd, t_map *data, int i, t_game *game);
void	check_data(t_map data);
int	    count_lines(int argc, char **argv);

//Clear
void	clear_array(char **map);
int		exit_game(t_game *game);
t_game	*save_window(t_game *game);

//Init
void	init_struct(t_game *game, int argc, char **argv);
void	game_init(t_game *game);
void	create_window(t_game *game);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	set_angle(t_game *game);

//Move
void	move(t_game *game, t_coord next, char *str);
void	move_player(t_game *game, int side);
void	write_move(t_game *game, char *str);
void	monster_move(t_game *game);
void	anim(t_game *game, int *i);
int		press_key(int keycode, t_game *game);
int		monster_next_move(t_game *game, int next_x);
void	print_move(t_game *game);

//Texture
void	texture_load(t_game **game);
void	load_one_texture(t_game *game, t_img *tex, char *path);
t_img	*texture_choice(t_game *game, char c, int y, int x);
char    *get_sprite_color(t_img *tex, int x, int y, int size);

//Draw
void	draw(t_game *game, int x, int y);
int		color_trans(t_img *tex, char *color);
void	draw_frame(t_game *game);
int		my_mlx_pixel_get(t_img t, int x, int y);
int		redraw(t_game *game);

//Utils
int	get_array_size(char **map);
int	get_size(t_coord res, char **map);
int	is_valid_position(t_game *game, t_coord next);

#endif
