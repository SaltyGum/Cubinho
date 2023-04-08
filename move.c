/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 09:14:14 by dvargas           #+#    #+#             */
/*   Updated: 2023/04/08 09:26:09 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_cub3d.h"

// Temos um "problema"
//por algum motivo o GRID com as coordenadas de map_grid nnao esta vindo com 0 mas sim com 48(chao) e 49(parede)
//possivelmente no futuro teremos que resolver isso mas para agora acredito nao dar maiores problemas.
int move_is_valid(t_cub3d *blk, float move_x, float move_y)
{
	int map_grid_x;
	int map_grid_y;

	map_grid_x = floor(move_x / TILE_SIZE);
	map_grid_y = floor(move_y / TILE_SIZE);
	//For Debug proposions
	//printf("Grid_X: %d\n", map_grid_x);
	//printf("Grid_y:%d\n\n", map_grid_y);
	//printf("GRID = %d\n\n\n", blk->map->map.map[map_grid_y][map_grid_x]);
	if(blk->map->map.map[map_grid_y][map_grid_x] != 49) // isso aqui deveria ser != 0 mas por algum motivo a localizacao das paredes esta como 49
	{
		blk->player.x = move_x;
		blk->player.y = move_y;
		return (1);
	}
	return (0);
}

int move_to_front(t_cub3d *blk)
{
	float move_step = blk->player.walk_direction * blk->player.walk_speed;
	double move_x;
	double move_y;

	move_x = blk->player.x + cos(blk->player.rotation_angle) * move_step;
	move_y = blk->player.y + sin(blk->player.rotation_angle) * move_step;
	return(move_is_valid(blk, move_x, move_y));
}

int move_to_back(t_cub3d *blk)
{
	float move_step = blk->player.walk_direction * blk->player.walk_speed;
	double move_x;
	double move_y;

	move_x = blk->player.x + cos(blk->player.rotation_angle) * move_step;
	move_y = blk->player.y + sin(blk->player.rotation_angle) * move_step;
	return(move_is_valid(blk, move_x, move_y));
}

int rotate_player(t_cub3d *blk)
{
	blk->player.rotation_angle += blk->player.turn_direction * blk->player.turn_speed * 0.0091;
	return(1);
}

int move_player(t_cub3d *blk)
{
	int move;
	move = 0;
	if(blk->player.turn_direction != 0)
		move += rotate_player(blk);
	if(blk->player.walk_direction == 1)
		move += move_to_front(blk);
	if(blk->player.walk_direction == -1)
		move += move_to_back(blk);
	return(move);
}