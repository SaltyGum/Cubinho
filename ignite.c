/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ignite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:27:36 by jeluiz4           #+#    #+#             */
/*   Updated: 2023/04/21 20:50:02 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_cub3d.h"

void	init_mlx_imgs(t_cub3d *blk)
{
	int	map_x;
	int	map_y;

	set_minimap_size(blk);
	map_x = (blk->map->map.width * TILE_SIZE * MINIMAP_SCALE) / blk->scale + 11;
	map_y = (blk->map->map.height * TILE_SIZE * MINIMAP_SCALE)
		/ blk->scale + 11;
	blk->mlx = mlx_init();
	blk->win = mlx_new_window(blk->mlx, WIDTH, HEIGHT, "CUB3D");
	blk->game.img = mlx_new_image(blk->mlx, WIDTH, HEIGHT);
	blk->game.addr = (int *) mlx_get_data_addr(blk->game.img,
			&blk->game.bits_per_pixel,
			&blk->game.line_length, &blk->game.endian);
	blk->minimap.img = mlx_new_image(blk->mlx, map_x, map_y);
	blk->minimap.addr = (int *) mlx_get_data_addr(blk->minimap.img,
			&blk->minimap.bits_per_pixel, &blk->minimap.line_length,
			&blk->minimap.endian);
}

float	set_direction(char c)
{
	if (c == 'N')
		return ((3 * PI) / 2);
	if (c == 'S')
		return (PI / 2);
	if (c == 'W')
		return (PI);
	if (c == 'E')
		return (0);
	return (0);
}

void	init_texture_image(t_cub3d *blk, t_img *tmp, char *texture)
{
	tmp->img = NULL;
	tmp->addr = NULL;
	tmp->width = 0;
	tmp->height = 0;
	tmp->bits_per_pixel = 32;
	tmp->line_length = tmp->width * (tmp->bits_per_pixel / 8);
	tmp->endian = 0;
	tmp->img = mlx_xpm_file_to_image(blk->mlx,
			texture, &tmp->width, &tmp->height);
	if (tmp->img == NULL || tmp->width != 64 || tmp->height != 64)
		printf("This map has broken images!!\n");
	tmp->addr = (int *) mlx_get_data_addr(tmp->img,
			&tmp->bits_per_pixel, &tmp->line_length, &tmp->endian);
	return ;
}

void	init_textures(t_cub3d *blk)
{
	init_texture_image(blk, &blk->textureimg[NO], blk->map->no_texture);
	init_texture_image(blk, &blk->textureimg[SO], blk->map->so_texture);
	init_texture_image(blk, &blk->textureimg[WE], blk->map->we_texture);
	init_texture_image(blk, &blk->textureimg[EA], blk->map->ea_texture);
}

void	player_init(t_cub3d *blk, t_player *player)
{
	player->x = (blk->map->map.playerpositionx) * TILE_SIZE;
	player->y = (blk->map->map.playerpositiony) * TILE_SIZE;
	player->width = 1;
	player->height = 1;
	player->rotation_angle = set_direction(blk->map->map.direction);
	player->walk_speed = 10;
	player->turn_speed = 90 * (PI / 180);
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->moved = 1;
	player->strafe = 0;
}
