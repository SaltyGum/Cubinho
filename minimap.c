/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 09:19:42 by dvargas           #+#    #+#             */
/*   Updated: 2023/04/08 09:36:11 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_cub3d.h"

void draw_minimap(t_cub3d *blk)
{
	size_t	i;
	size_t	j;
	char **map  = blk->map->map.map;

	i = 0;
	j = 0;
	while(i < blk->map->map.height)
	{
		j = 0;
		while(j < blk->map->map.width)
		{
			 if (map[i][j] == '1')
				draw_rectangle(blk, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE, RED_PIXEL);
			else if (map[i][j] == '0')
				draw_rectangle(blk, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE, WHITE_PIXEL);
			else
				draw_rectangle(blk, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE, GREY_PIXEL);
			j++;
		}
		i++;
	}
}

void draw_player(t_cub3d *blk)
{
	draw_rectangle(blk, blk->player.x, blk->player.y, blk->player.width, blk->player.height, 0xf1d2a2);
	draw_line(blk, blk->player.x, blk->player.y, blk->player.x + cos(blk->player.rotation_angle) * 20, blk->player.y + sin(blk->player.rotation_angle) * 20);
}

void minimap_render(t_cub3d *blk)
{
	draw_minimap(blk);
	draw_player(blk);
	mlx_put_image_to_window(blk->mlx, blk->win, blk->img, 0, 0);
}