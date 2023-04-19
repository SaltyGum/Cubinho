/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 08:34:25 by dvargas           #+#    #+#             */
/*   Updated: 2023/04/19 15:33:13 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_cub3d.h"

void	draw_sky(t_cub3d *blk, float wall_top_pix, int i, int *y)
{
	while (*y < wall_top_pix)
	{
		my_mlx_pixelput(&blk->game, i, *y, blk->map->ceil);
		(*y)++;
	}
}

void	draw_floor(t_cub3d *blk, int i, int *y)
{
	while (*y < HEIGHT)
	{
		my_mlx_pixelput(&blk->game, i, *y, blk->map->floor);
		(*y)++;
	}
}

void	draw_texture(t_cub3d *blk, t_projection *proj, int i, int y)
{
	t_pos	pos[1];

	pos[0].x = i;
	pos[0].y = y;
	if (blk->ray[i].is_hit_vertical
		&& blk->ray[i].is_ray_face_right)
		put_texture(blk, proj, *pos, WE);
	else if (blk->ray[i].is_hit_vertical
		&& blk->ray[i].is_ray_face_left)
		put_texture(blk, proj, *pos, EA);
	else if (!blk->ray[i].is_hit_vertical
		&& blk->ray[i].is_ray_face_up)
		put_texture(blk, proj, *pos, NO);
	else if (!blk->ray[i].is_hit_vertical
		&& blk->ray[i].is_ray_face_down)
		put_texture(blk, proj, *pos, SO);
}

void	generate3d_projection(t_cub3d *blk)
{
	t_projection	proj;
	int				i;
	int				y;

	i = 0;
	y = 0;
	while (i < NB_OF_RAYS)
	{
		init_projection(blk, &proj, i);
		y = 0;
		draw_sky(blk, proj.wall_top_pix, i, &y);
		set_x_offset(blk, &proj, i);
		y = proj.wall_top_pix;
		while (y < proj.wall_bot_pix)
		{
			set_y_offset(&proj, y);
			draw_texture(blk, &proj, i, y);
			y++;
		}
		y = proj.wall_bot_pix;
		draw_floor(blk, i, &y);
		i++;
	}
	mlx_put_image_to_window(blk->mlx, blk->win, blk->game.img, 0, 0);
}
