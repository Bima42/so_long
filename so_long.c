/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 14:13:44 by tpauvret          #+#    #+#             */
/*   Updated: 2021/11/20 18:19:29 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_lines(int argc, char **argv)
{
	int		nb_lines;
	int		fd;
	char	*line;
	
	nb_lines = 0;
	line = NULL;;
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

void	init(t_map *map)
{
	map->empty = 0;
	map->wall = 0;
	map->coin = 0;
	map->exit = 0;
	map->pos = 0;
}

void	check_error(char *line, t_map *data)
{
	int		i;

	i = 0;
	while (line[i] != '\n')
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
	check_error(line, data);
	return (line);
}

char	**parsing_map(int argc, char **argv)
{
	int		i;
	int		fd;
	int		nb_lines;
	char	**map;
	t_map	data;

	i = 0;
	init(&data);
	nb_lines = count_lines(argc, argv);
	fd = open(argv[1], O_RDONLY);
	map = malloc(sizeof(char *) * nb_lines);
	if (!map)
		return (NULL);
	while (nb_lines > 0)
	{
		map[i] = get_line(fd, &data);
		i++;
		nb_lines--;
	}
	return (map);
}

int	main(int argc, char **argv)
{
	char	**map;
	int i = 0;

	map = parsing_map(argc, argv);
	while (map != NULL)
	{
		printf("%s", map[i]);
		i++;
	}
	return (0);
}
