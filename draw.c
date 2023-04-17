/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 12:27:00 by jeluiz4           #+#    #+#             */
/*   Updated: 2023/04/17 14:40:16 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_cub3d.h"

// TO-DO: Colocar essas variaveis no blk pra diminuir isso a norma ta gritando;
//		  As da chamada da função também só pode ter 4 tem 5;

void	draw_line(t_cub3d *blk, float x0, float y0, float x1, float y1)
{
	int		i;
	int		dx;
	int		dy;
	int		steps;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;

	i = 0;
	dx = x1 - x0;
	dy = y1 - y0;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	y_inc = dy / (float)steps;
	x_inc = dx / (float)steps;
	x = x0;
	y = y0;
	while (i <= steps)
	{
		my_mlx_pixelput(blk, x, y, 0x0200200);
		x += x_inc;
		y += y_inc;
		i++;
	}
}

void	make_rectangle(t_cub3d *game, t_pos pos[2], int color)
{
	double	movex;

	while (pos[0].y < pos[1].y)
	{
		movex = pos[0].x;
		while (movex < pos[1].x)
		{
			my_mlx_pixelput(game, movex, pos[0].y, color);
			movex += 1;
		}
		pos[0].y += 1;
	}
}
/*
void	generate3d_projection(t_cub3d *blk)
{
	float	perp_dist;
	float	dist_proj_plane;
	float	proj_wall_hei;
	float	wall_strip_height;
	float	wall_top_pix;
	float	wall_bot_pix;
	float	y;
	int		i;

	i = 0;
	//mlx_clear_window(blk->mlx ,blk->win);
	while (i < NB_OF_RAYS)
	{
		perp_dist = blk->ray[i].distance * cos(blk->ray[i].ray_angle
				- blk->player.rotation_angle);
		dist_proj_plane = ((float)WIDTH / 2.0) / tan(FOV_ANGLE / 2.0);
		proj_wall_hei = (TILE_SIZE / perp_dist) * dist_proj_plane;
		wall_strip_height = proj_wall_hei;
		wall_top_pix = ((float)HEIGHT / 2.0) - (wall_strip_height / 2.0);
		if (wall_top_pix < 0)
			wall_top_pix = 0;
		wall_bot_pix = ((float)HEIGHT / 2.0) + (wall_strip_height / 2.0);
		if (wall_bot_pix > HEIGHT)
			wall_bot_pix = (float)HEIGHT;
		//Sky Color
		y = 0;
		while (y < wall_top_pix)
		{
			my_mlx_pixelput(blk, i, y, blk->map->ceil);
			y++;
		}
		int	texture_offset_x;
		if (blk->ray[i].is_hit_vertical)
			texture_offset_x = (int)blk->ray[i].hit_y_wall % TEXTURE_HEIGHT;
		else
			texture_offset_x = (int)blk->ray[i].hit_x_wall % TEXTURE_WIDTH;
		//WallColors
		y = wall_top_pix;
		while (y < wall_bot_pix)
		{
			int			dist_from_top;
			int			texture_offset_y;
			u_int32_t	texel_color;

			dist_from_top = y + (wall_strip_height / 2) - (HEIGHT / 2);
			texture_offset_y = dist_from_top
				* ((float)TEXTURE_HEIGHT / wall_strip_height);
			if (blk->ray[i].is_hit_vertical
				&& blk->ray[i].is_ray_face_right)
			{
				texel_color = blk->textureimg[WE].addr[(TEXTURE_WIDTH
						* texture_offset_y) + texture_offset_x];
				my_mlx_pixelput(blk, i, y, texel_color);
			}
			else if (blk->ray[i].is_hit_vertical
				&& blk->ray[i].is_ray_face_left)
			{
				texel_color = blk->textureimg[EA].addr[(TEXTURE_WIDTH
						* texture_offset_y) + texture_offset_x];
				my_mlx_pixelput(blk, i, y, texel_color);
			}
			else if (!blk->ray[i].is_hit_vertical
				&& blk->ray[i].is_ray_face_up)
			{
				texel_color = blk->textureimg[NO].addr[(TEXTURE_WIDTH
						* texture_offset_y) + texture_offset_x];
				my_mlx_pixelput(blk, i, y, texel_color);
			}
			else if (!blk->ray[i].is_hit_vertical
				&& blk->ray[i].is_ray_face_down)
			{
				texel_color = blk->textureimg[SO].addr[(TEXTURE_WIDTH
						* texture_offset_y) + texture_offset_x];
				my_mlx_pixelput(blk, i, y, texel_color);
			}
			y++;
		}
		//Floor Color
		y = wall_bot_pix;
		while (y < HEIGHT)
		{
			my_mlx_pixelput(blk, i, y, blk->map->floor);
			y++;
		}
		i++;
	}
	mlx_put_image_to_window(blk->mlx, blk->win, blk->img, 0, 0);
}
*/
