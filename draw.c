/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 12:27:00 by jeluiz4           #+#    #+#             */
/*   Updated: 2023/04/17 18:06:35 by jeluiz4          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_cub3d.h"

// TO-DO: Colocar essas variaveis no blk pra diminuir isso a norma ta gritando;
//		  As da chamada da função também só pode ter 4 tem 5;

void	draw_line(t_cub3d *blk, t_pos wid, t_pos hei)
{
	int		i;
	int		dx;
	int		dy;
	int		steps;
	t_pos	inc;

	i = 0;
	dx = wid.y - wid.x;
	dy = hei.y - hei.x;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	inc.y = dy / (float)steps;
	inc.x = dx / (float)steps;
	while (i <= steps)
	{
		my_mlx_pixelput(blk, wid.x, hei.x, 0x6c7a89);
		wid.x += inc.x;
		hei.x += inc.y;
		i++;
	}
}

void	draw_player(t_cub3d *blk)
{
	t_pos	pos[2];

	pos[0].x = blk->player.x * MINIMAP_SCALE;
	pos[0].y = blk->player.y * MINIMAP_SCALE;
	pos[1].x = blk->player.width * MINIMAP_SCALE + pos[0].x;
	pos[1].y = blk->player.height * MINIMAP_SCALE + pos[0].y;
	make_rectangle(blk, pos, 0xf1d2a2);
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

void	get_rect(t_cub3d *blk, int x, int y, int color)
{
	t_pos	pos[2];
	float	sides;

	sides = (TILE_SIZE / 4) * MINIMAP_SCALE2;
	pos[0].x = x;
	pos[0].y = y;
	pos[1].x = x + sides;
	pos[1].y = y + sides;
	make_rectangle(blk, pos, color);
}
