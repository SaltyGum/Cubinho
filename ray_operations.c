/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 08:17:04 by dvargas           #+#    #+#             */
/*   Updated: 2023/04/17 12:24:10 by jeluiz4          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_cub3d.h"

void	nray_init(t_new_ray *ray, float ray_angle)
{
	ray->ray_face_down = (ray_angle > 0) & (ray_angle < PI);
	ray->ray_face_up = !ray->ray_face_down;
	ray->ray_face_right = (ray_angle < 0.5 * PI) | (ray_angle > 1.5 * PI);
	ray->ray_face_left = !ray->ray_face_right;
	ray->hor_xstep = 0;
	ray->hor_ystep = 0;
	ray->hor_wall_hit = FALSE;
	ray->hor_wall_hit_x = 0;
	ray->hor_wall_hit_y = 0;
	ray->next_hor_touch_x = 0;
	ray->next_hor_touch_y = 0;
	ray->hor_x_to_check = 0;
	ray->hor_y_to_check = 0;
	ray->hor_hit_distance = 0;
	ray->vert_xstep = 0;
	ray->vert_ystep = 0;
	ray->vert_wall_hit = FALSE;
	ray->vert_wall_hit_x = 0;
	ray->vert_wall_hit_y = 0;
	ray->next_vert_touch_x = 0;
	ray->next_vert_touch_y = 0;
	ray->vert_x_to_check = 0;
	ray->vert_y_to_check = 0;
	ray->ver_hit_distance = 0;
}

void	set_hor_step(t_cub3d *blk, t_new_ray *nray, float ray_angle)
{
	nray->next_hor_touch_y = floor(blk->player.y / TILE_SIZE) * TILE_SIZE;
	if (nray->ray_face_down)
		nray->next_hor_touch_y += TILE_SIZE;
	nray->next_hor_touch_x = blk->player.x + (nray->next_hor_touch_y \
								- blk->player.y) / tan(ray_angle);
	nray->hor_ystep = TILE_SIZE;
	if (nray->ray_face_up)
		nray->hor_ystep *= -1;
	nray->hor_xstep = TILE_SIZE / tan(ray_angle);
	if (nray->ray_face_left && nray->hor_xstep > 0)
		nray->hor_xstep *= -1;
	if (nray->ray_face_right && nray->hor_xstep < 0)
		nray->hor_xstep *= -1;
}

void	set_vert_step(t_cub3d *blk, t_new_ray *nray, float ray_angle)
{
	nray->next_vert_touch_x = floor(blk->player.x / TILE_SIZE) * TILE_SIZE;
	if (nray->ray_face_right)
		nray->next_vert_touch_x += TILE_SIZE;
	nray->next_vert_touch_y = blk->player.y + (nray->next_vert_touch_x - \
								blk->player.x) * tan(ray_angle);
	nray->vert_xstep = TILE_SIZE;
	if (nray->ray_face_left)
		nray->vert_xstep *= -1;
	nray->vert_ystep = TILE_SIZE * tan(ray_angle);
	if (nray->ray_face_up && nray->vert_ystep > 0)
		nray->vert_ystep *= -1;
	if (nray->ray_face_down && nray->vert_ystep < 0)
		nray->vert_ystep *= -1;
}

void	find_hor_hit(t_cub3d *blk, t_new_ray *nray)
{
	while (nray->next_hor_touch_x >= 0
		&& nray->next_hor_touch_x <= blk->map->map.width * TILE_SIZE
		&& nray->next_hor_touch_y >= 0
		&& nray->next_hor_touch_y <= blk->map->map.height * TILE_SIZE)
	{
		nray->hor_x_to_check = nray->next_hor_touch_x;
		nray->hor_y_to_check = nray->next_hor_touch_y;
		if (nray->ray_face_up)
			nray->hor_y_to_check -= 1;
		if (is_a_wall(blk, nray->hor_x_to_check, nray->hor_y_to_check))
		{
			nray->hor_wall_hit_x = nray->next_hor_touch_x;
			nray->hor_wall_hit_y = nray->next_hor_touch_y;
			nray->hor_wall_hit = TRUE;
			break ;
		}
		else
		{
			nray->next_hor_touch_x += nray->hor_xstep;
			nray->next_hor_touch_y += nray->hor_ystep;
		}
	}
}

void	find_vert_hit(t_cub3d *blk, t_new_ray *nray)
{
	while (nray->next_vert_touch_x >= 0 \
			&& nray->next_vert_touch_x <= blk->map->map.width * TILE_SIZE \
			&& nray->next_vert_touch_y >= 0 \
			&& nray->next_vert_touch_y <= blk->map->map.height * TILE_SIZE)
	{
		nray->vert_x_to_check = nray->next_vert_touch_x;
		nray->vert_y_to_check = nray->next_vert_touch_y;
		if (nray->ray_face_left)
			nray->vert_x_to_check -= 1;
		if (is_a_wall(blk, nray->vert_x_to_check, nray->vert_y_to_check))
		{
			nray->vert_wall_hit_x = nray->next_vert_touch_x;
			nray->vert_wall_hit_y = nray->next_vert_touch_y;
			nray->vert_wall_hit = TRUE;
			break ;
		}
		else
		{
			nray->next_vert_touch_x += nray->vert_xstep;
			nray->next_vert_touch_y += nray->vert_ystep;
		}
	}
}
