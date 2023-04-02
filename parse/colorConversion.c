/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorConversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:51:47 by dvargas           #+#    #+#             */
/*   Updated: 2023/04/02 07:40:51 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_cub3d.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

// ESSA MERDA FUNCIONA PARCIALMENTE
int	rgb_to_hex(char *color)
{
	char	**tmp;
	int		rgb[3];
	int		i;
	int		glass;

	i = 0;
	tmp = ft_split(color, ',');
	if (!tmp)
		return (1);
	while (i < 3)
	{
		rgb[i] = ft_atoi(tmp[i]);
		i++;
	}
	glass = create_rgb(rgb[0], rgb[1], rgb[2]);
	free_matrix((void **)tmp);
	return (glass);
}