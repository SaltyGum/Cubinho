/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   igniteAndError.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:30:54 by dvargas           #+#    #+#             */
/*   Updated: 2023/04/02 07:40:56 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_cub3d.h"

void	parse_ignite(t_parse *parse)
{
	parse->no_texture = NULL;
	parse->so_texture = NULL;
	parse->we_texture = NULL;
	parse->ea_texture = NULL;
	parse->floor = -1;
	parse->ceil = -1;
	parse->map.map = NULL;
	parse->map.height = 0;
	parse->map.width = 0;
	parse->map.playerpositionx = -1;
	parse->map.playerpositiony = -1;
}

void	ft_error(char *error)
{
	printf("%s", error);
}

void	free_map(t_map *map)
{
	size_t	i;

	i = 0;
	if (!map)
		return ;
	if (map->map)
	{
		while (i < map->height)
		{
			free(map->map[i]);
			i++;
		}
		free(map->map);
	}
}

void	*free_matrix(void **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	return (NULL);
}

void	*free_parse(t_parse *parse)
{
	if (parse->no_texture)
		free(parse->no_texture);
	if (parse->so_texture)
		free(parse->so_texture);
	if (parse->ea_texture)
		free(parse->ea_texture);
	if (parse->we_texture)
		free(parse->we_texture);
	free_map(&parse->map);
	free(parse);
	return (NULL);
}
