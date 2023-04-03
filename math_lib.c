/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_lib.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:53:08 by jeluiz4           #+#    #+#             */
/*   Updated: 2023/04/02 07:37:17 by dvargas          ###   ########.fr       */
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
