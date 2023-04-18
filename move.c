/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 09:14:14 by dvargas           #+#    #+#             */
/*   Updated: 2023/04/17 22:46:55 by jeluiz4          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_cub3d.h"

int	move_is_valid(t_cub3d *blk, float move_x, float move_y)
{
	int	map_grid_x;
	int	map_grid_y;

	map_grid_x = floor(move_x / TILE_SIZE);
	map_grid_y = floor(move_y / TILE_SIZE);
	if (blk->map->map.map[map_grid_y][map_grid_x] == '0')
	{
		blk->player.x = (int) move_x;
		blk->player.y = (int) move_y;
		return (1);
	}
	return (0);
}

int	move_to_left(t_cub3d *blk)
{
	float	move_step;
	double	move_x;
	double	move_y;

	move_step = blk->player.walk_speed * 2;
	printf("ANGULO DA DESGRACA %f\n", blk->player.rotation_angle);
	move_x = blk->player.x + sin(blk->player.rotation_angle) * move_step;
	move_y = blk->player.y;
	return (move_is_valid(blk, move_x, move_y));
}

int	move_to_right(t_cub3d *blk)
{
	float	move_step;
	double	move_x;

	move_step = blk->player.walk_speed;
	move_x = blk->player.x + sin(blk->player.rotation_angle) * move_step;
	move_x = blk->player.y;
	return (move_is_valid(blk, move_x, 0));
}

int	move_to_front(t_cub3d *blk)
{
	float	move_step;
	double	move_x;
	double	move_y;

	move_step = blk->player.walk_direction * blk->player.walk_speed;
	move_x = blk->player.x + cos(blk->player.rotation_angle) * move_step;
	move_y = blk->player.y + sin(blk->player.rotation_angle) * move_step;
	return (move_is_valid(blk, move_x, move_y));
}

int	move_to_back(t_cub3d *blk)
{
	float	move_step;
	double	move_x;
	double	move_y;

	move_step = blk->player.walk_direction * blk->player.walk_speed;
	move_x = blk->player.x + cos(blk->player.rotation_angle) * move_step;
	move_y = blk->player.y + sin(blk->player.rotation_angle) * move_step;
	return (move_is_valid(blk, move_x, move_y));
}

int	rotate_player(t_cub3d *blk)
{
	blk->player.rotation_angle += blk->player.turn_direction
		* blk->player.turn_speed * 0.045;
	if (blk->player.rotation_angle > (2 * PI))
		blk->player.rotation_angle = blk->player.rotation_angle - (2 * PI);
	else if (blk->player.rotation_angle < 0.0)
		blk->player.rotation_angle = (2 * PI) - blk->player.rotation_angle;
	return (1);
}

int	move_player(t_cub3d *blk)
{
	int	move;

	move = 0;
	if (blk->player.turn_direction != 0)
		move += rotate_player(blk);
	if (blk->player.walk_direction == 1)
		move += move_to_front(blk);
	if (blk->player.walk_direction == -1)
		move += move_to_back(blk);
	if (blk->player.walk_direction == 2)
		move += move_to_right(blk);
	if (blk->player.walk_direction == -2)
		move += move_to_left(blk);
	return (move);
}
