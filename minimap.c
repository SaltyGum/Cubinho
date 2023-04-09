/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 09:19:42 by dvargas           #+#    #+#             */
/*   Updated: 2023/04/09 10:20:33 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_cub3d.h"

void draw_minimap(t_cub3d *blk)
{
	size_t	i;
	size_t	j;
	char **map  = blk->map->map.map;

	i = 0;
	j = 0;
	while(i < blk->map->map.height)
	{
		j = 0;
		while(j < blk->map->map.width)
		{
			if (map[i][j] == '1')
				draw_rectangle(blk, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE, RED_PIXEL);
			else if (map[i][j] == '0')
				draw_rectangle(blk, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE, WHITE_PIXEL);
			else
				draw_rectangle(blk, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE, GREY_PIXEL);
			j++;
		}
		i++;
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

void draw_player(t_cub3d *blk)
{
	draw_rectangle(blk, blk->player.x, blk->player.y, blk->player.width, blk->player.height, 0xf1d2a2);
	draw_line(blk, blk->player.x, blk->player.y, blk->player.x + cos(blk->player.rotation_angle) * 20, blk->player.y + sin(blk->player.rotation_angle) * 20);
}

float norm_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if(angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

float points_distance(float x1, float y1, float x2, float y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

int is_a_wall(t_cub3d *blk, float x, float y)
{
	if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT) {
        return TRUE;
    }
	int map_grid_x = floor(x / TILE_SIZE);
	int map_grid_y = floor(y / TILE_SIZE);
	if(blk->map->map.map[map_grid_y][map_grid_x] == '0')
		return (FALSE);
	return (TRUE);
}

void cast_one_ray(t_cub3d *blk, float ray_angle, int ray_id)
{
	ray_angle = norm_angle(ray_angle);
	int ray_face_down = ray_angle > 0 && ray_angle < PI;
	int ray_face_up =  !ray_face_down;
	int ray_face_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
	int ray_face_left = !ray_face_right;

	float xintercept;
	float yintercept;
	float xstep;
	float ystep;

	//VERIFICAR GRID HORIZONTAL

	int hor_wall_hit = FALSE;
	float hor_wall_hit_x = 0;
	float hor_wall_hit_y = 0;
	//int hor_wall_content = 0;

	yintercept = floor(blk->player.y / TILE_SIZE) * TILE_SIZE;
	if(ray_face_down)
		yintercept += TILE_SIZE;

	xintercept = blk->player.x + (yintercept - blk->player.y) / tan(ray_angle);

	ystep = TILE_SIZE;
	if(ray_face_up)
		ystep *= -1;
	else
		ystep *= 1;

	xstep = TILE_SIZE / tan(ray_angle);
	if(ray_face_left && xstep > 0)
		xstep *= -1;
	else
		ystep *= 1;

	if(ray_face_right && xstep < 0)
		xstep *= -1;
	else
		ystep *= 1;

	float next_hor_touch_x = xintercept;
	float next_hor_touch_y = yintercept;

	while (next_hor_touch_x >= 0 && next_hor_touch_x <= WIDTH && next_hor_touch_y >= 0 && next_hor_touch_y <= HEIGHT) {
        float x_to_check = next_hor_touch_x;
        float y_to_check = next_hor_touch_y;
		if(ray_face_up)
			y_to_check -= 1;

        if (is_a_wall(blk, x_to_check, y_to_check)) {
            // found a wall hit
            hor_wall_hit_x = next_hor_touch_x;
            hor_wall_hit_y = next_hor_touch_y;
            //hor_wall_content = blk->map->map.map[(int)floor(y_to_check / TILE_SIZE)][(int)floor(x_to_check / TILE_SIZE)];
            hor_wall_hit = TRUE;
            break;
        } else {
            next_hor_touch_x += xstep;
            next_hor_touch_y += ystep;
        }
	}


// VERTICAL GRID COLISION
	int vert_wall_hit = FALSE;
	float vert_wall_hit_x = 0;
	float vert_wall_hit_y = 0;
	//int vert_wall_content = 0;

	xintercept = floor(blk->player.x / TILE_SIZE) * TILE_SIZE;
	if(ray_face_right)
		xintercept += TILE_SIZE;

	yintercept = blk->player.y + (xintercept - blk->player.x) * tan(ray_angle);

	xstep = TILE_SIZE;
	if(ray_face_left)
		xstep *= -1;
	else
		ystep *= 1;

	ystep = TILE_SIZE * tan(ray_angle);
	if(ray_face_up && ystep > 0)
		ystep *= -1;
	else
		ystep *= 1;
	if(ray_face_down && ystep < 0)
		ystep *= -1;
	else
		ystep *= 1;

	float next_vert_touch_x = xintercept;
	float next_vert_touch_y = yintercept;

	while (next_vert_touch_x >= 0 && next_vert_touch_x <= WIDTH && next_vert_touch_y >= 0 && next_vert_touch_y <= HEIGHT) {
        float x_to_check = next_vert_touch_x;
		if(ray_face_left)
			x_to_check -= 1;
        float y_to_check = next_vert_touch_y;

        if (is_a_wall(blk, x_to_check, y_to_check)) {
            // found a wall hit
            vert_wall_hit_x = next_vert_touch_x;
            vert_wall_hit_y = next_vert_touch_y;
            //vert_wall_content = blk->map->map.map[(int)floor(x_to_check / TILE_SIZE)][(int)floor(y_to_check / TILE_SIZE)];
            vert_wall_hit = TRUE;
            break;
        } else {
            next_vert_touch_x += xstep;
            next_vert_touch_y += ystep;
        }
	}

	//Calcular e escolher qual hit vamos escolher
   float hor_hit_distance;
	if(hor_wall_hit == TRUE)
		hor_hit_distance = points_distance(blk->player.x, blk->player.y, hor_wall_hit_x, hor_wall_hit_y);
	else
		hor_hit_distance = __FLT_MAX__;
	float ver_hit_distance;
	if(vert_wall_hit == TRUE)
		ver_hit_distance = points_distance(blk->player.x, blk->player.y, vert_wall_hit_x, vert_wall_hit_y);
	else
		ver_hit_distance = __FLT_MAX__;

	if(ver_hit_distance < hor_hit_distance)
	{
		blk->ray[ray_id].distance = ver_hit_distance;
		blk->ray[ray_id].hit_x_wall = vert_wall_hit_x;
        blk->ray[ray_id].hit_y_wall = vert_wall_hit_y;
        //blk->ray[ray_id].hit_content = vert_wall_content;
        blk->ray[ray_id].is_hit_vertical = TRUE;
	}
	else
	{
		blk->ray[ray_id].distance = hor_hit_distance;
		blk->ray[ray_id].hit_x_wall = hor_wall_hit_x;
        blk->ray[ray_id].hit_y_wall = hor_wall_hit_y;
        //blk->ray[ray_id].hit_content = hor_wall_content;
        blk->ray[ray_id].is_hit_vertical = FALSE;
	}
	blk->ray[ray_id].ray_angle = ray_angle;
	blk->ray[ray_id].is_ray_face_down = ray_face_down;
	blk->ray[ray_id].is_ray_face_up = ray_face_up;
	blk->ray[ray_id].is_ray_face_left = ray_face_left;
	blk->ray[ray_id].is_ray_face_right = ray_face_right;
}

void cast_rays(t_cub3d *blk)
{
	float ray_angle = blk->player.rotation_angle - (FOV_ANGLE / 2);
	int ray_id = 0;

	while(ray_id < NB_OF_RAYS)
	{
		cast_one_ray(blk, ray_angle, ray_id);
		ray_angle += FOV_ANGLE / NB_OF_RAYS;
		ray_id++;
	}
}
void render_rays(t_cub3d *blk)
{
	int i = 0;
	while(i < NB_OF_RAYS)
	{
		draw_line(blk, blk->player.x, blk->player.y, blk->ray[i].hit_x_wall, blk->ray[i].hit_y_wall);
		i++;
	}
}
void minimap_render(t_cub3d *blk)
{
	draw_minimap(blk);
	draw_player(blk);
	render_rays(blk);
	mlx_put_image_to_window(blk->mlx, blk->win, blk->img, 0, 0);
}