/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_lib.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:53:08 by jeluiz4           #+#    #+#             */
/*   Updated: 2023/04/21 19:34:27 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_cub3d.h"

double	degtorad(double degrees)
{
	return (degrees * (PI / 180.0));
}

double	radtodeg(double radius)
{
	return (radius * (180.0 / PI));
}

void	my_mlx_pixelput(t_img *data, int x, int y, int color)
{
	char	*pixel;

	pixel = (char *) data->addr
		+ (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

float	norm_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

float	points_distance(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
