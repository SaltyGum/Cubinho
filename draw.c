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
	float		wallStripHeight;
	float		wallTopPixel;
	float		y;
	float		wallBottomPixel;
	int		i;

	i = 0;
	//mlx_clear_window(blk->mlx ,blk->win);
	while (i < NB_OF_RAYS)
	{
		perpDistance = blk->ray[i].distance * cos(blk->ray[i].ray_angle - blk->player.rotation_angle);
		distanceProjPlane = ((float)WIDTH / 2.0) / tan(FOV_ANGLE / 2.0);
		projectedWallHeight = (TILE_SIZE / perpDistance) * distanceProjPlane;
		wallStripHeight = projectedWallHeight;
		wallTopPixel = ((float)HEIGHT/ 2.0) - (wallStripHeight / 2.0);
		if (wallTopPixel < 0)
			wallTopPixel = 0;

		wallBottomPixel = ((float)HEIGHT / 2.0) + (wallStripHeight / 2.0);
		if	(wallBottomPixel > HEIGHT)
			wallBottomPixel = (float)HEIGHT;
		//Sky Color
		y = 0;
		while(y < wallTopPixel)
		{
			my_mlx_pixelput(blk, i, y, 0xFF87CEFA);
			y++;}

		int textureOffsetX;
        if (blk->ray[i].is_hit_vertical)
            textureOffsetX = (int)blk->ray[i].hit_y_wall % TEXTURE_HEIGHT;
        else
            textureOffsetX = (int)blk->ray[i].hit_x_wall % TEXTURE_WIDTH;

		//WallColors
		// wallBottomPixel = wallBottomPixel > HEIGHT ? HEIGHT : wallBottomPixel;
		// render the wall from wallTopPixel to wallBottomPixel
		y = wallTopPixel;
		while (y < wallBottomPixel)
		{
			int distanceFromTop = y + (wallStripHeight / 2) - (HEIGHT / 2);
			int textureOffsetY = distanceFromTop * ((float)TEXTURE_HEIGHT / wallStripHeight);
			u_int32_t texelColor;
			if (blk->ray[i].is_hit_vertical && blk->ray[i].is_ray_face_right)
			{
				texelColor = blk->textureimg[WE].addr[(TEXTURE_WIDTH * textureOffsetY) + textureOffsetX];
				my_mlx_pixelput(blk, i, y, texelColor);
			}
			else if (blk->ray[i].is_hit_vertical && blk->ray[i].is_ray_face_left)
			{
				texelColor = blk->textureimg[EA].addr[(TEXTURE_WIDTH * textureOffsetY) + textureOffsetX];
				my_mlx_pixelput(blk, i, y, texelColor);
			}
			else if(!blk->ray[i].is_hit_vertical && blk->ray[i].is_ray_face_up)
			{
				texelColor = blk->textureimg[NO].addr[(TEXTURE_WIDTH * textureOffsetY) + textureOffsetX];
				my_mlx_pixelput(blk, i, y, texelColor);
			}
			else if(!blk->ray[i].is_hit_vertical && blk->ray[i].is_ray_face_down)
			{
				texelColor = blk->textureimg[SO].addr[(TEXTURE_WIDTH * textureOffsetY) + textureOffsetX];
				my_mlx_pixelput(blk, i, y, texelColor);
			}
			//[(WIDTH * y) + i] = blk->ray[i].is_hit_vertical ? 0xFFFFFFFF : 0xFFCCCCCC;
			y++;
		}


		//Floor Color
		y = wallBottomPixel;
		while(y < HEIGHT)
		{
			my_mlx_pixelput(blk, i, y, 0xFFF4A460);
			y++;}
		i++;
	}
	mlx_put_image_to_window(blk->mlx, blk->win, blk->img, 0, 0);
}
