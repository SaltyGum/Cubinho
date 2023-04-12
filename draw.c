/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:32:10 by jeluiz4           #+#    #+#             */
/*   Updated: 2023/04/12 09:47:34 by jeluiz4          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_cub3d.h"

void draw_line(t_cub3d *blk, float x0, float y0, float x1, float y1)
{
  int dx = x1 - x0;
  int dy = y1 - y0;
  int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
  float x_inc = dx / (float)steps;
  float y_inc = dy / (float)steps;
  float x = x0;
  float y = y0;

	int i = 0;
  while(i <= steps)
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

void	generate3DProjection(t_cub3d *blk) {
    for (int i = 0; i < NB_OF_RAYS; i++) {
        float perpDistance = blk->ray[i].distance * cos(blk->ray[i].ray_angle - blk->player.rotation_angle);
        float distanceProjPlane = (WIDTH / 2) / tan(FOV_ANGLE / 2);
        float projectedWallHeight = (TILE_SIZE / perpDistance) * distanceProjPlane;

        int wallStripHeight = (int)projectedWallHeight;

        int wallTopPixel = (HEIGHT / 2) - (wallStripHeight / 2);
        wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

        int wallBottomPixel = (HEIGHT / 2) + (wallStripHeight / 2);

		if	(wallBottomPixel > HEIGHT)
			wallBottomPixel = HEIGHT;
		//wallBottomPixel = wallBottomPixel > HEIGHT ? HEIGHT : wallBottomPixel;
        // render the wall from wallTopPixel to wallBottomPixel
        for (int y = wallTopPixel; y < wallBottomPixel; y++) {
			if (blk->ray[i].is_hit_vertical)
				my_mlx_pixelput(blk, wallBottomPixel, wallTopPixel, 0xFFFFFFFF);
			else
            	my_mlx_pixelput(blk, wallBottomPixel, wallTopPixel, 0xFFCCCCCC);
			//[(WIDTH * y) + i] = blk->ray[i].is_hit_vertical ? 0xFFFFFFFF : 0xFFCCCCCC;
        }
    }
}
