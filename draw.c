/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 12:27:00 by jeluiz4           #+#    #+#             */
/*   Updated: 2023/04/19 16:04:33 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_cub3d.h"

void	draw_line(t_img *img, t_pos wid, t_pos hei)
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
		my_mlx_pixelput(img, wid.x, hei.x, 0x6c7a89);
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
	make_rectangle(&blk->minimap, pos, 0xf1d2a2);
}

void	make_rectangle(t_img *game, t_pos pos[2], int color)
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

	sides = TILE_SIZE * MINIMAP_SCALE;
	pos[0].x = x;
	pos[0].y = y;
	pos[1].x = x + sides;
	pos[1].y = y + sides;
	make_rectangle(&blk->minimap, pos, color);
}
