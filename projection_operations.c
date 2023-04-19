/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_operations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:28:08 by dvargas           #+#    #+#             */
/*   Updated: 2023/04/19 15:42:29 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_cub3d.h"

void	init_projection(t_cub3d *blk, t_projection *prj, int i)
{
	prj->perp_dist = blk->ray[i].distance * cos(blk->ray[i].ray_angle
			- blk->player.rotation_angle);
	prj->dist_proj_plane = ((float)WIDTH / 2.0) / tan(FOV_ANGLE / 2.0);
	prj->proj_wall_hei = (TILE_SIZE / prj->perp_dist) * prj->dist_proj_plane;
	prj->wall_strip_height = prj->proj_wall_hei;
	prj->wall_top_pix = ((float)HEIGHT / 2.0) - (prj->wall_strip_height / 2.0);
	if (prj->wall_top_pix < 0)
		prj->wall_top_pix = 0;
	prj->wall_bot_pix = ((float)HEIGHT / 2.0) + (prj->wall_strip_height / 2.0);
	if (prj->wall_bot_pix > HEIGHT)
		prj->wall_bot_pix = (float)HEIGHT;
}

void	set_x_offset(t_cub3d *blk, t_projection *proj, int i)
{
	if (blk->ray[i].is_hit_vertical)
		proj->texture_offset_x = (int)blk->ray[i].hit_y_wall % TEXTURE_HEIGHT;
	else
		proj->texture_offset_x = (int)blk->ray[i].hit_x_wall % TEXTURE_WIDTH;
}

void	put_texture(t_cub3d *blk, t_projection *proj, t_pos pos, int size)
{
	proj->texel_color = blk->textureimg[size].addr[(TEXTURE_WIDTH
			* proj->texture_offset_y) + proj->texture_offset_x];
	my_mlx_pixelput(&blk->game, pos.x, pos.y, proj->texel_color);
}

void	set_y_offset(t_projection *proj, int y)
{
	proj->dist_from_top = y + (proj->wall_strip_height / 2) - (HEIGHT / 2);
	proj->texture_offset_y = proj->dist_from_top
		* ((float)TEXTURE_HEIGHT / proj->wall_strip_height);
}
