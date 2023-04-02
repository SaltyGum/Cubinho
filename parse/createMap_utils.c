/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createMap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:37:53 by dvargas           #+#    #+#             */
/*   Updated: 2023/04/02 07:40:58 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_cub3d.h"

int	check_extension(char *str)
{
	char	*extension;

	extension = ft_strchr(str, '.');
	if (extension != NULL && ft_strcmp(extension, ".cub") == 0)
		return (1);
	else
		return (0);
}

int	ft_str_search(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	set_map_width(char **map)
{
	int	ret;
	int	i;
	int	glass;

	ret = 0;
	i = 0;
	glass = 0;
	while (map[i])
	{
		glass = ft_strlen(map[i]);
		if (glass > ret)
			ret = glass;
		i++;
	}
	return (ret);
}

int	set_map_height(char **ret)
{
	int	i;

	i = 0;
	while (ret[i])
		i++;
	return (i);
}

void	update_width_height(t_map *map)
{
	map->width = set_map_width(map->map);
	map->height = set_map_height(map->map);
}
