/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 20:22:41 by dvargas           #+#    #+#             */
/*   Updated: 2023/04/21 20:35:57 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_cub3d.h"

void	set_player_to_zero(t_parse *parse)
{
	size_t	x;
	size_t	y;

	x = parse->map.playerpositionx;
	y = parse->map.playerpositiony;
	parse->map.map[y][x] = '0';
}

void	set_player_direction(t_parse *parse)
{
	size_t	x;
	size_t	y;
	char	**map;

	x = -1;
	y = -1;
	map = parse->map.map;
	while (++y < parse->map.height)
	{
		x = -1;
		while (++x < ft_strlen(map[y]))
		{
			if (map[y][x] == 'N')
				parse->map.direction = 'N';
			if (map[y][x] == 'S')
				parse->map.direction = 'S';
			if (map[y][x] == 'W')
				parse->map.direction = 'W';
			if (map[y][x] == 'E')
				parse->map.direction = 'E';
		}
	}
	parse->map.tile_width = parse->map.width * TILE_SIZE;
	parse->map.tile_height = parse->map.height * TILE_SIZE;
	set_player_to_zero(parse);
}

t_parse	*parse_map(char *path)
{
	int		fd_map;
	t_parse	*parse;
	char	*line;

	parse = malloc(sizeof(t_parse));
	parse_ignite(parse);
	fd_map = open(path, O_RDONLY);
	if (fd_map < 0)
		return (ft_error("Unable to open the map"), free_parse(parse));
	if (!check_extension(path))
		return (ft_error("Extension map should be .cub"), free_parse(parse));
	line = get_next_line(fd_map);
	if (!extract_assets(fd_map, &line, parse))
		return (ft_error("Assets error \n"), free(line), free_parse(parse));
	parse->map.map = create_map(fd_map, &line);
	if (!parse->map.map)
		return (ft_error("Map creation gone wrong \n"), free_parse(parse));
	parse->map.width = set_map_width(parse->map.map);
	parse->map.height = set_map_height(parse->map.map);
	if (!find_player(parse, -1, -1, 0))
		return (ft_error("No player in map"), free(line), free_parse(parse));
	if (!validate_map(*parse))
		return (ft_error("Not a valid map\n"), free(line), free_parse(parse));
	set_player_direction(parse);
	return (parse);
}
