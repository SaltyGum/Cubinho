/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validateMap_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:45:23 by dvargas           #+#    #+#             */
/*   Updated: 2023/04/02 07:40:55 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_cub3d.h"

char	*fill_line_size(char *line, int size)
{
	int		i;
	char	*ret;

	if (!line)
		return (NULL);
	ret = ft_strdup(line);
	i = ft_strlen(ret);
	free(line);
	while (i < size)
	{
		ft_swapjoinchar(&ret, ' ');
		i++;
	}
	return (ret);
}

char	**map_inside_box(t_map *map)
{
	char	**box;
	size_t	i;
	size_t	j;

	i = -1;
	j = 1;
	box = ft_calloc(sizeof(char *), (map->height + 3));
	while (++i < map->height + 2)
		box[i] = ft_calloc(sizeof(char), (map->width + 3));
	ft_memset(box[0], '2', map->width + 2);
	ft_memset(box[map->height + 1], '2', map->width + 2);
	while (j < map->height + 1)
	{
		box[j][0] = '2';
		box[j][map->width + 1] = '2';
		ft_memcpy(&box[j][1], map->map[j - 1], map->width);
		ft_memset(&box[j][map->width + 2], '\0', 1);
		j++;
	}
	free_map(map);
	return (box);
}
