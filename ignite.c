/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ignite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:27:36 by jeluiz4           #+#    #+#             */
/*   Updated: 2023/04/16 09:53:53 by jeluiz4          ###   ########.fr       */
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

t_img *init_texture_image(t_cub3d *blk, char *texture)
{
	t_img *tmp;

	tmp = ft_calloc(sizeof(t_img), 1);
	tmp->img = NULL;
	tmp->addr = NULL;
	tmp->width = 0;
	tmp->height = 0;
	tmp->pixel_bits = 32;
	tmp->size_line = blk->textureimg->width * (tmp->pixel_bits / 8);
	tmp->endian = 0;

	tmp->img = mlx_xpm_file_to_image(blk->mlx, texture, &tmp->width, &tmp->height);
	tmp->addr = (int *)mlx_get_data_addr(tmp->img, &tmp->pixel_bits, &tmp->size_line, &tmp->endian);
	return(tmp);
}

void	init_textures(t_cub3d *blk)
{
	blk->textureimg[NO] = *init_texture_image(blk, blk->map->no_texture);
	blk->textureimg[SO] = *init_texture_image(blk, blk->map->so_texture);
	blk->textureimg[WE] = *init_texture_image(blk, blk->map->we_texture);
	blk->textureimg[EA] = *init_texture_image(blk, blk->map->ea_texture);
}


void	player_init(t_cub3d *blk, t_player *player)
{
	player->x = (blk->map->map.playerpositionx) * TILE_SIZE;
	player->y = (blk->map->map.playerpositiony) * TILE_SIZE;
	player->width = 1;
	player->height = 1;
	player->rotation_angle = set_direction(blk->map->map.direction);
	player->walk_speed = 5;
	player->turn_speed = 45 * (PI / 180);
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->moved = 0;
	//init_textures(blk);
}
