/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_lib.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:53:08 by jeluiz4           #+#    #+#             */
/*   Updated: 2023/04/12 16:36:00 by jeluiz4          ###   ########.fr       */
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

void	my_mlx_pixelput(t_cub3d *data, int x, int y, int color)
{
	char	*pixel;

	pixel = data->addr
		+ (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}
