/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validateMap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:41:12 by dvargas           #+#    #+#             */
/*   Updated: 2023/04/16 11:19:42 by jeluiz4          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_cub3d.h"

int	find_player(t_parse *parse, size_t x, size_t y, int ret)
{
	int		position[2];
	char	**map;

	ret = 0;
	map = parse->map.map;
	while (++y < parse->map.height)
	{
		x = -1;
		while (++x < ft_strlen(map[y]))
		{
			if (map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'W' || map[y][x] == 'E')
			{
			position[0] = x + 1;
			position[1] = y + 1;
			ret++;
			}
		}
	}
	if (ret == 1)
	{
		parse->map.playerpositionx = position[0] - 1;
		parse->map.playerpositiony = position[1] - 1;
		return (1);
	}
	return (0);
}

int	map_is_open(t_map *map, size_t x, size_t y)
{
	char	cell;
	int		is_open;

	is_open = 0;
	cell = map->map[y][x];
	if (cell == ' ' || cell == '2')
		return (1);
	if (cell == '9' || cell == '1')
		return (0);
	else if (cell == '0' || !ft_strchr("NSWE", cell))
		map->map[y][x] = '9';
	is_open += map_is_open(map, x - 1, y);
	is_open += map_is_open(map, x + 1, y);
	is_open += map_is_open(map, x, y - 1);
	is_open += map_is_open(map, x, y + 1);
	return (is_open);
}

char	**map_xerox(t_parse parse)
{
	size_t	j;
	char	**xerox;

	j = 0;
	xerox = malloc(sizeof(char *) * (parse.map.height + 1));
	if (!xerox)
		return (NULL);
	while (j < parse.map.height)
	{
		xerox[j] = ft_strdup(parse.map.map[j]);
		j++;
	}
	xerox[j] = NULL;
	return (xerox);
}

t_map	*fill_map(t_parse parse)
{
	size_t	i;
	t_map	*map_cpy;

	i = 0;
	map_cpy = malloc(sizeof(t_map) * 1);
	if (!map_cpy)
		return (NULL);
	map_cpy->map = map_xerox(parse);
	update_width_height(map_cpy);
	while (i < map_cpy->height)
	{
		if (ft_strlen(map_cpy->map[i]) < map_cpy->width)
			map_cpy->map[i] = fill_line_size(map_cpy->map[i], map_cpy->width);
		i++;
	}
	map_cpy->map = map_inside_box(map_cpy);
	update_width_height(map_cpy);
	return (map_cpy);
}

int	validate_map(t_parse parse)
{
	t_map	*to_valid;
	int		ret;
	int		x;
	int		y;

	x = parse.map.playerpositionx + 1;
	y = parse.map.playerpositiony + 1;
	to_valid = fill_map(parse);
	if (!to_valid)
		return (1);
	if (!map_is_open(to_valid, x, y))
		ret = 1;
	else
		ret = 0;
	free_map(to_valid);
	free(to_valid);
	return (ret);
}
