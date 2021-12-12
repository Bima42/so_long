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

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "mlx.h"
#include "get_next_line/get_next_line.h"

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
	char	**map;
	void	*mlx;
	void	*mlx_win;
	int		size;
	t_coord	screen_res;
	t_img	img;
	t_img	wall;
	t_img	player;
	t_img	door;
	t_img	item;
}				t_game;

//Parsing_map
char	**parsing_map(int argc, char **argv);
void	check_wall(char **map, t_map data);
void	check_wall_2(char **map, t_map data);
void	check_wall_3(char **map, size_t len);
void	write_error(void);

//Check_error
void	init(t_map *map, int lines);
void	set_data(char *line, t_map *data);
char	*get_line(int fd, t_map *data);
void	check_data(t_map data);
int	    count_lines(int argc, char **argv);

//Manage window
void	my_mlx_pixel_put(t_img *map, int x, int y, int color);

//Draw
void	draw_map(t_game *game);
void	texture_load(t_game **game);
char    *get_sprite_color(t_img *tex, int x, int y, int cubesize);
void	draw(t_game *game, int x, int y);
int    color_trans(t_img *tex, char *color);
void	draw_frame(t_game *game);
int    my_mlx_pixel_get(t_img t, int x, int y);
t_img	*texture_choice(t_game *game, char c);
void	load_one_texture(t_game *game, t_img *tex, char *path);
void	create_window(t_game *game);
int	get_size(t_coord res, char **map);
int	get_array_size(char **map);

#endif
