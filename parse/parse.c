/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 20:22:41 by dvargas           #+#    #+#             */
/*   Updated: 2023/04/02 07:40:56 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_cub3d.h"

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
		return (ft_error("Deu ruim no mapa \n"), free_parse(parse));
	parse->map.width = set_map_width(parse->map.map);
	parse->map.height = set_map_height(parse->map.map);
	if (!find_player(parse, -1, -1, 0))
		return (ft_error("no Player"), free(line), free_parse(parse));
	if (!validate_map(*parse))
		return (ft_error("Not a valid map\n"), free(line), free_parse(parse));
	return (parse);
}