/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ignite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:27:36 by jeluiz4           #+#    #+#             */
/*   Updated: 2023/04/08 09:15:46 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "lib_cub3d.h"

void	player_init(t_cub3d *blk, t_player *player)
{
	player->x = blk->map->map.playerpositionx * TILE_SIZE;
	player->y = blk->map->map.playerpositiony * TILE_SIZE;
	player->width = 1;
	player->height = 1;
	player->rotation_angle = PI / 2;
	player->walk_speed = 1;
	player->turn_speed = 45 * (PI / 180);
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->moved = 0;
}
