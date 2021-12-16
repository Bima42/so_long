#include "so_long_bonus.h"

int	get_size(t_coord res, char **map)
{
	t_coord	size;
	int		len_line;
	int		len_array;

	len_line = ft_strlen(*map);
	len_array = get_array_size(map);
	size.x = res.x / len_line;
	size.y = res.y / len_array;
	if (size.x <= size.y)
	{
		if (size.y * len_line > res.x)
			size.y = res.x - 1;
	}
	else
	{
		if (size.x * len_array > res.y)
			res.x = res.y - 1;
	}
	if (size.x < size.y)
	{
		if (size.x < 1)
			return (1);
		return (size.x);
	}
	return (size.y);
}

int	get_array_size(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	is_valid_position(t_game *game, t_coord next)
{
	int	out;

	out = ((next.x > 0 && next.x < (int)ft_strlen(*game->map))
			&& (next.y > 0 && next.y < (int)get_array_size(game->map)));
	return (out);
}
