#include "so_long.h"

void	texture_load(t_game **game)
{
	load_one_texture(*game, &(*game)->player, "./asset/player.xpm");
	load_one_texture(*game, &(*game)->wall, "./asset/wall.xpm");
	load_one_texture(*game, &(*game)->door, "./asset/door.xpm");
	load_one_texture(*game, &(*game)->item, "./asset/item.xpm");
}

void	load_one_texture(t_game *game, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, path, &tex->width, &tex->height);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_pixel, &tex->line_length, &tex->endian);
}

t_img	*texture_choice(t_game *game, char c)
{
	if (c == 'P')
		return (&game->player);
	else if (c == '1')
		return (&game->wall);
	else if (c == 'E')
		return (&game->door);
	else if (c == 'C')
		return (&game->item);
	else if (c == '0')
		return (NULL);
	return (NULL);
}

char    *get_sprite_color(t_img *tex, int x, int y, int size)
{
    int		txt_x;
    int		txt_y;
    char	*color;

    txt_x = 0;
    txt_y = 0;
    txt_x = tex->width / (100 / (((double)x / size) * 100.0));
    txt_y = tex->height / (100 / (((double)y / size) * 100.0));
    color = tex->addr + ((4 * tex->width * txt_y) + (4 * txt_x));
    return (color);
}
