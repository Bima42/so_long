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
#include <mlx.h>
#include "get_next_line/get_next_line.h"

typedef struct	s_map
{
	void	*img;
	char	*addr;
	int	bits_pixel;
	int	line_length;
	int	endian;
	int	empty;
	int	wall;
	int	coin;
	int	exit;
	int	pos;
	int	nb_lines;
	int	x;
	int	y;
}				t_map;

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

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
void	my_mlx_pixel_put(t_map *map, int x, int y, int color);

#endif
