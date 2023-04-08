/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:32:10 by jeluiz4           #+#    #+#             */
/*   Updated: 2023/04/08 09:22:49 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_cub3d.h"

void draw_line(t_cub3d *blk, int x0, int y0, int x1, int y1)
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
	my_mlx_pixelput(blk, x, y, RED_PIXEL);
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

void	draw_rectangle(t_cub3d *game, int x, int y, int width, int height, int color)
{
    t_pos pos[2];

    pos[0].x = x;
    pos[0].y = y;
    pos[1].x = x + width;
    pos[1].y = y + height;
    make_rectangle(game, pos, color);
}