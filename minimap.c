/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:02:22 by jeluiz4           #+#    #+#             */
/*   Updated: 2023/04/17 17:59:42 by jeluiz4          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_cub3d.h"

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

void	draw_minimap(t_cub3d *blk)
{
	size_t	i;
	size_t	j;
	char	**map;
	float	siz;

	siz = (TILE_SIZE / 4) * MINIMAP_SCALE2;
	map = blk->map->map.map;
	i = 0;
	while (i < blk->map->map.height)
	{
		j = 0;
		while (j < blk->map->map.width)
		{
			if (map[i][j] == '1')
				get_rect(blk, j * siz, i * siz, RED_PIXEL);
			else if (map[i][j] == '0')
				get_rect(blk, j * siz, i * siz, WHITE_PIXEL);
			else
				get_rect(blk, j * siz, i * siz, GREY_PIXEL);
			j++;
		}
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

int	is_a_wall(t_cub3d *blk, float x, float y)
{
	int	map_grid_x;
	int	map_grid_y;

	map_grid_x = floor(x / TILE_SIZE);
	map_grid_y = floor(y / TILE_SIZE);
	if (x < 0 || x > blk->map->map.width * TILE_SIZE
		|| y < 0 || y > blk->map->map.height * TILE_SIZE)
		return (TRUE);
	if (blk->map->map.map[map_grid_y][map_grid_x] == '0')
		return (FALSE);
	return (TRUE);
}

void	cast_rays(t_cub3d *blk)
{
	float	ray_angle;
	int		ray_id;

	ray_angle = blk->player.rotation_angle - (FOV_ANGLE / 2);
	ray_id = 0;
	while (ray_id < NB_OF_RAYS)
	{
		cast_one_ray(blk, ray_angle, ray_id);
		ray_angle += FOV_ANGLE / NB_OF_RAYS;
		ray_id++;
	}
}

void	render_rays(t_cub3d *blk)
{
	int		i;
	t_pos	wid;
	t_pos	hei;

	i = 0;
	while (i < NB_OF_RAYS)
	{
		wid.x = blk->player.x * MINIMAP_SCALE;				//x0
		wid.y = blk->ray[i].hit_x_wall * MINIMAP_SCALE;		//x1
		hei.x = blk->player.y * MINIMAP_SCALE;				//y0
		hei.y = blk->ray[i].hit_y_wall * MINIMAP_SCALE;		//y1
		draw_line(blk, wid, hei);
		i++;
	}
}

void	minimap_render(t_cub3d *blk)
{
	draw_minimap(blk);
	draw_player(blk);
	render_rays(blk);
	mlx_put_image_to_window(blk->mlx, blk->win, blk->img, 0, 0);
}

/*	OLD DRAW_LINE
	draw_line(blk,	blk->player.x * MINIMAP_SCALE,//x0
					blk->player.y * MINIMAP_SCALE,//y0
					blk->ray[i].hit_x_wall * MINIMAP_SCALE,//x1
					blk->ray[i].hit_y_wall * MINIMAP_SCALE);//y1
*/
