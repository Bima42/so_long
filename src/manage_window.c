#include "so_long.h"

void	my_mlx_pixel_put(t_img *map, int x, int y, int color)
{
	char	*dst;

	dst = map->addr + (y * map->line_length + x * (map->bits_pixel / 8));
	*(unsigned int*)dst = color;
}
