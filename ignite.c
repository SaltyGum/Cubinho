/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ignite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:27:36 by jeluiz4           #+#    #+#             */
/*   Updated: 2023/04/18 15:33:44 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_cub3d.h"

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

void	init_texture_image(t_cub3d *blk,t_img *tmp, char *texture)
{
	tmp->img = NULL;
	tmp->addr = NULL;
	tmp->width = 0;
	tmp->height = 0;
	tmp->pixel_bits = 32;
	tmp->size_line = tmp->width * (tmp->pixel_bits / 8);
	tmp->endian = 0;
	tmp->img = mlx_xpm_file_to_image(blk->mlx,
			texture, &tmp->width, &tmp->height);
	if (tmp->img == NULL || tmp->width != 64 || tmp->height != 64)
		printf("This map has broken images!!\n");
	tmp->addr = (int *)mlx_get_data_addr(tmp->img,
			&tmp->pixel_bits, &tmp->size_line, &tmp->endian);
	return;
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
}
