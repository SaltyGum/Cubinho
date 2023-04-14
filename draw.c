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

int    create_trgb(int t,int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	draw_sprite(t_cub3d *blk, int top, int bot)
{
	t_sprite	nw;
	int	i = 0, j = 0, x = HEIGHT, posx = 0, p = 0;;

	//void	*mlx_xpm_file_to_image(t_xvar *xvar,char *file,int *width,int *height)
	nw.img = mlx_xpm_file_to_image(blk->mlx, "/home/saltygum/Área de trabalho/uniao.xmp", &top, &x);
	nw.addr = mlx_get_data_addr(nw.img, &nw.bits_per_pixel, &nw.line_length, &nw.endian);
	while (i < x)
	{
		posx = 0;
		p = 0;
		while (j < top)
		{
			if (nw.endian == 1)
			{
				nw.color->t = (int)nw.addr[(i * nw.line_length) + p];
				nw.color->r = (int)nw.addr[(i * nw.line_length) + p + 1];
				nw.color->g = (int)nw.addr[(i * nw.line_length) + p + 2];
				nw.color->b = (int)nw.addr[(i * nw.line_length) + p + 3];
			}
			else
			{
				nw.color->t = (int)nw.addr[(i * nw.line_length) + p + 3];
				nw.color->r = (int)nw.addr[(i * nw.line_length) + p + 2];
				nw.color->g = (int)nw.addr[(i * nw.line_length) + p + 1];
				nw.color->b = (int)nw.addr[(i * nw.line_length) + p];
			}
			my_mlx_pixelput(blk->img, posx, i, create_trgb(nw.color->t, nw.color->r, nw.color->g, nw.color->b));
			posx++;
			p+=4;
		}
		i++;
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
		y = 0;
		while(y < wallTopPixel)
		{
			my_mlx_pixelput(blk, i, y, 0xFF333333);
			y++;}
		// wallBottomPixel = wallBottomPixel > HEIGHT ? HEIGHT : wallBottomPixel;
		// render the wall from wallTopPixel to wallBottomPixel
		y = wallTopPixel;
		while (y < wallBottomPixel)
		{
			if (blk->ray[i].is_hit_vertical)
				my_mlx_pixelput(blk, i, y, 0xFF00FF00);
			else
				my_mlx_pixelput(blk, i, y, 0xFFCCCCCC);
			//[(WIDTH * y) + i] = blk->ray[i].is_hit_vertical ? 0xFFFFFFFF : 0xFFCCCCCC;
			y++;
		}
		y = wallBottomPixel;
		/*while(y < HEIGHT)
		  {
		  my_mlx_pixelput(blk, i, y, 0xFF777777);
		  y++;}
		 */

		i++;
	}
	mlx_put_image_to_window(blk->mlx, blk->win, blk->img, 0, 0);
	draw_sprite(blk, y, i);
}
