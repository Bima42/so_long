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
		else
		{
			write(1, "Error, caracters can't be used.\n", 32);
			exit(0);
		}
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
