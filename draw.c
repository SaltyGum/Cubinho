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

void	generate3d_projection(t_cub3d *blk)
{
	float	perpDistance;
	float	distanceProjPlane;
	float	projectedWallHeight;
	int		wallStripHeight;
	int		wallTopPixel;
	int		y;
	int		wallBottomPixel;
	int		i;

	i = 0;
	mlx_clear_window(blk->mlx ,blk->win);
	while (i < NB_OF_RAYS)
	{
		perpDistance = blk->ray[i].distance * cos(blk->ray[i].ray_angle - blk->player.rotation_angle);
		distanceProjPlane = (WIDTH / 2) / tan(FOV_ANGLE / 2);
		projectedWallHeight = (TILE_SIZE / perpDistance) * distanceProjPlane;
		wallStripHeight = (int)projectedWallHeight;
		wallTopPixel = (HEIGHT / 2) - (wallStripHeight / 2);
		if (wallTopPixel < 0)
			wallTopPixel = 0;
		else
			wallTopPixel = wallTopPixel;
		wallBottomPixel = (HEIGHT / 2) + (wallStripHeight / 2);
		if	(wallBottomPixel > HEIGHT)
			wallBottomPixel = HEIGHT;
		else
			wallBottomPixel = wallBottomPixel;
		// wallBottomPixel = wallBottomPixel > HEIGHT ? HEIGHT : wallBottomPixel;
		// render the wall from wallTopPixel to wallBottomPixel
		y = wallTopPixel;
		while (y < wallBottomPixel)
		{
			if (blk->ray[i].is_hit_vertical)
				my_mlx_pixelput(blk, i, y, 0x00FFFFFF);
			else
				my_mlx_pixelput(blk, i, y, 0x00FF64FF);
			//[(WIDTH * y) + i] = blk->ray[i].is_hit_vertical ? 0xFFFFFFFF : 0xFFCCCCCC;
			y++;
		}
		i++;
	}
	mlx_put_image_to_window(blk->mlx, blk->win, blk->img, 0, 0);
}
