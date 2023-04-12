/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 draw.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dvargas < dvargas@student.42.rio>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2023/03/19 14:32:10 by jeluiz4		   #+#	  #+#			  */
/*	 Updated: 2023/04/12 16:21:37 by jeluiz4		  ###	########.fr		  */
/*																			  */
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

void	generate3d_projection(t_cube *blk)
	{
	for (int i = 0; i < NUM_RAYS; i++) {
		float perpDistance = rays[i].distance * cos(rays[i].rayAngle - player.rotationAngle);
		float distanceProjPlane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
		float projectedWallHeight = (TILE_SIZE / perpDistance) * distanceProjPlane;

		int wallStripHeight = (int)projectedWallHeight;

		int wallTopPixel = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);
		wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

		int wallBottomPixel = (WINDOW_HEIGHT / 2) + (wallStripHeight / 2);
		wallBottomPixel = wallBottomPixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : wallBottomPixel;

		// render the wall from wallTopPixel to wallBottomPixel
		for (int y = wallTopPixel; y < wallBottomPixel; y++) {
			colorBuffer[(WINDOW_WIDTH * y) + i] = rays[i].wasHitVertical ? 0xFFFFFFFF : 0xFFCCCCCC;
		}
	}
}
