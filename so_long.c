/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 14:13:44 by tpauvret          #+#    #+#             */
/*   Updated: 2021/11/22 14:59:36 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_lines(int argc, char **argv)
{
	int		nb_lines;
	int		fd;
	char	*line;
	
	nb_lines = 0;
	line = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit(0);
	if (argc == 2)
	{
		while (1)
		{
			line = get_next_line(fd);
			//ADD CHECK ERROR HERE
			if (line == NULL)
			{
				if (close(fd) == -1)
					exit(0);
				return (nb_lines);
			}
			nb_lines++;
		}
	}
	return (nb_lines);
}

void	init(t_map *map, int lines)
{
	map->empty = 0;
	map->wall = 0;
	map->coin = 0;
	map->exit = 0;
	map->pos = 0;
	map->nb_lines = lines - 1;
}

void	set_data(char *line, t_map *data)
{
	int		i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '0')
			data->empty++;
		else if (line[i] == '1')
			data->wall++;
		else if (line[i] == 'C')
			data->coin++;
		else if (line[i] == 'E')
			data->exit++;
		else if (line[i] == 'P')
			data->pos++;
		i++;
	}
}

char	*get_line(int fd, t_map *data)
{
	char	*line;

	line = get_next_line(fd);
	set_data(line, data);
	return (line);
}

void	check_data(t_map data)
{
	if (data.coin < 1)
	{
		write(1, "Error, no coin found.\n", 22);
		exit(0);
	}
	if (data.exit < 1)
	{
		write(1, "Error, no exit found.\n", 22);
		exit(0);
	}
	if (data.pos < 1)
	{
		write(1, "Error, no position found.\n", 26);
		exit(0);
	}
}

void	write_error(void)
{
	write(1, "Error wall\n", 11);
	exit(0);
}

void	check_wall(char **map, t_map data)
{
	size_t	len;
	int	i;

	i = 0;
	len = ft_strlen(map[0]) - 1;
	while (i != data.nb_lines)
	{
		if (len == ft_strlen(map[i]) - 1)
			i++;
		else
			write_error();
	}
	i = 0;
	while (map[0][i])
	{
		if (map[0][i] == '1')
			i++;
		else
			write_error();
	}
	i = 0;
	while (map[data.nb_lines][i])
	{
		if (map[data.nb_lines][i] == '1')
			i++;
		else
			write_error();
	}
	i = 0;
	while (map[i])
	{
		if (map[i][0] == '1')
			i++;
		else
			write_error();
	}
	i = 0;
	while (map[i])
	{
		if (map[i][len] == '1')
			i++;
		else
			write_error();
	}
	if (i >= (int)len)
	{
		write(1, "Map is not rectangular\n", 23);
		exit(0);
	}
}

char	**parsing_map(int argc, char **argv)
{
	int		i;
	int		fd;
	int		nb_lines;
	char	**map;
	t_map	data;

	i = 0;
	nb_lines = count_lines(argc, argv);
	init(&data, nb_lines);
	fd = open(argv[1], O_RDONLY);
	map = malloc(sizeof(char *) * nb_lines + 1);
	if (!map)
		return (NULL);
	while (nb_lines-- > 0)
		map[i++] = get_line(fd, &data);
	map[i] = NULL;
	if (close(fd) == -1)
		exit(0);
	check_data(data);
	check_wall(map, data);
	return (map);
}

int	main(int argc, char **argv)
{
	char	**map;
	int i = 0;

	map = parsing_map(argc, argv);
	while (i < 5)
	{
		printf("%s\n", map[i]);
		i++;
	}
	return (0);
}
