#include "so_long.h"

char	**parsing_map(int argc, char **argv, t_game *game)
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
	game->nb_lines = nb_lines - 1;
	while (nb_lines-- > 0)
	{
		map[i] = get_line(fd, &data, i, game);
		i++;
	}
	map[i] = 0;
	if (close(fd) == -1)
		exit(0);
	check_data(data);
	check_wall(map, data);
	game->coin_count = data.coin;
	return (map);
}

void	write_error(char **map)
{
	write(1, "Error wall\n", 11);
	clear_array(map);
	exit(0);
}

void	check_wall(char **map, t_map data)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(map[0]) - 1;
	while (i != data.nb_lines)
	{
		if (len == ft_strlen(map[i]) - 1)
			i++;
		else
			write_error(map);
	}
	check_wall_2(map, data);
	check_wall_3(map, len);
}

void	check_wall_2(char **map, t_map data)
{
	int	i;

	i = 0;
	while (map[0][i])
	{
		if (map[0][i] == '1')
			i++;
		else
			write_error(map);
	}
	i = 0;
	while (map[data.nb_lines][i])
	{
		if (map[data.nb_lines][i] == '1')
			i++;
		else
			write_error(map);
	}
}

void	check_wall_3(char **map, size_t len)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i][0] == '1')
			i++;
		else
			write_error(map);
	}
	i = 0;
	while (map[i])
	{
		if (map[i][len] == '1')
			i++;
		else
			write_error(map);
	}
	if (i >= (int)len)
	{
		write(1, "Map is not rectangular\n", 23);
		clear_array(map);
		exit(0);
	}
}
