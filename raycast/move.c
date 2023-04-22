/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 09:14:14 by dvargas           #+#    #+#             */
/*   Updated: 2023/04/22 08:13:31 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_cub3d.h"

int	move_is_valid(t_cub3d *blk, float move_x, float move_y)
{
	int	map_grid_x;
	int	map_grid_y;

	map_grid_x = floor(move_x / TILE_SIZE);
	map_grid_y = floor(move_y / TILE_SIZE);
	if (blk->map->map.map[map_grid_y][map_grid_x] == '0')
	{
		blk->player.x = move_x;
		blk->player.y = move_y;
		return (1);
	}
	return (0);
}

int	strafe(t_cub3d *blk, int x)
{
	float	move_step;
	float	angle;
	double	move_x;
	double	move_y;

	angle = blk->player.rotation_angle + blk->player.turn_direction \
		* blk->player.walk_speed;
	move_step = x * blk->player.walk_speed;
	angle += (3 * PI / 2);
	move_x = blk->player.x - cos(angle) * move_step;
	move_y = blk->player.y - sin(angle) * move_step;
	return (move_is_valid(blk, move_x, move_y));
}

int	move_to_front(t_cub3d *blk)
{
	float	move_step;
	double	move_x;
	double	move_y;

	move_step = 1 * blk->player.walk_speed;
	move_x = blk->player.x + cos(blk->player.rotation_angle) * move_step;
	move_y = blk->player.y + sin(blk->player.rotation_angle) * move_step;
	return (move_is_valid(blk, move_x, move_y));
}

int	move_to_back(t_cub3d *blk)
{
	float	move_step;
	double	move_x;
	double	move_y;

	move_step = -1 * blk->player.walk_speed;
	move_x = blk->player.x + cos(blk->player.rotation_angle) * move_step;
	move_y = blk->player.y + sin(blk->player.rotation_angle) * move_step;
	return (move_is_valid(blk, move_x, move_y));
}

int	rotate_player(t_cub3d *blk)
{
	blk->player.rotation_angle += blk->player.turn_direction
		* blk->player.turn_speed * 0.045;
	if (blk->player.rotation_angle > (2 * PI))
		blk->player.rotation_angle -= (2 * PI);
	else if (blk->player.rotation_angle < 0.0)
		blk->player.rotation_angle = (2 * PI) - blk->player.rotation_angle;
	return (1);
}
