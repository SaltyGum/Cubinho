/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 06:43:46 by dvargas           #+#    #+#             */
/*   Updated: 2023/04/22 08:13:15 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_cub3d.h"

void	copy_ray_in_blk(t_cub3d *blk, t_new_ray *nray, float angle, int ray_id)
{
	if (nray->ver_hit_distance < nray->hor_hit_distance)
	{
		blk->ray[ray_id].distance = nray->ver_hit_distance;
		blk->ray[ray_id].hit_x_wall = nray->vert_wall_hit_x;
		blk->ray[ray_id].hit_y_wall = nray->vert_wall_hit_y;
		blk->ray[ray_id].is_hit_vertical = TRUE;
	}
	else
	{
		blk->ray[ray_id].distance = nray->hor_hit_distance;
		blk->ray[ray_id].hit_x_wall = nray->hor_wall_hit_x;
		blk->ray[ray_id].hit_y_wall = nray->hor_wall_hit_y;
		blk->ray[ray_id].is_hit_vertical = FALSE;
	}
	blk->ray[ray_id].ray_angle = angle;
	blk->ray[ray_id].is_ray_face_down = nray->ray_face_down;
	blk->ray[ray_id].is_ray_face_up = nray->ray_face_up;
	blk->ray[ray_id].is_ray_face_left = nray->ray_face_left;
	blk->ray[ray_id].is_ray_face_right = nray->ray_face_right;
}

void	cast_one_ray(t_cub3d *blk, float ray_angle, int ray_id)
{
	t_new_ray	nray;

	ray_angle = norm_angle(ray_angle);
	nray_init(&nray, ray_angle);
	set_hor_step(blk, &nray, ray_angle);
	set_vert_step(blk, &nray, ray_angle);
	find_hor_hit(blk, &nray);
	find_vert_hit(blk, &nray);
	if (nray.hor_wall_hit == TRUE)
		nray.hor_hit_distance = points_distance(blk->player.x,
				blk->player.y, nray.hor_wall_hit_x, nray.hor_wall_hit_y);
	else
		nray.hor_hit_distance = __FLT_MAX__;
	if (nray.vert_wall_hit == TRUE)
		nray.ver_hit_distance = points_distance(blk->player.x,
				blk->player.y, nray.vert_wall_hit_x, nray.vert_wall_hit_y);
	else
		nray.ver_hit_distance = __FLT_MAX__;
	copy_ray_in_blk(blk, &nray, ray_angle, ray_id);
}
