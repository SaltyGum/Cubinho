/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkAssets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:31:38 by dvargas           #+#    #+#             */
/*   Updated: 2023/04/21 20:22:12 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_cub3d.h"

int	extract_texture(char *line, t_parse *parse)
{
	char	*path;
	int		i;

	i = 2;
	while (line && line[i] == ' ')
		i++;
	path = line + i;
	clean_path(path);
	if (!path)
		return (0);
	if (!ft_strncmp("NO", line, 2) && can_save(parse, path, 1) == 1)
		return (parse->no_texture = ft_strdup(path), 1);
	if (!ft_strncmp("SO", line, 2) && can_save(parse, path, 2))
		return (parse->so_texture = ft_strdup(path), 1);
	if (!ft_strncmp("EA", line, 2) && can_save(parse, path, 3))
		return (parse->ea_texture = ft_strdup(path), 1);
	if (!ft_strncmp("WE", line, 2) && can_save(parse, path, 4))
		return (parse->we_texture = ft_strdup(path), 1);
	return (0);
}

int	extract_color(char *line, t_parse *parse)
{
	int		i;
	char	*color;

	i = 0;
	while (line && !ft_isdigit(line[i]))
		i++;
	color = line + i;
	if (!validade_color(color))
		return (0);
	if (!ft_strncmp("F", line, 1) && can_save(parse, NULL, 5))
	{
		return (parse->floor = rgb_to_hex(color), 1);
	}
	if (!ft_strncmp("C", line, 1) && can_save(parse, NULL, 6))
	{
		return (parse->ceil = rgb_to_hex(color), 1);
	}
	return (0);
}

int	is_color(char *color)
{
	if (color[0] == 'F' || color[0] == 'C')
		return (1);
	else
		return (0);
}

int	is_texture(char *line)
{
	if (!line || ft_strlen(line) < 3)
		return (0);
	if (!ft_strncmp("NO", line, 2))
		return (1);
	if (!ft_strncmp("SO", line, 2))
		return (1);
	if (!ft_strncmp("EA", line, 2))
		return (1);
	if (!ft_strncmp("WE", line, 2))
		return (1);
	return (0);
}

int	extract_assets(int fd_map, char **line, t_parse *parse)
{
	int	result;

	result = 0;
	while (*line != NULL)
	{
		if (is_texture(*line))
		{
			if (!extract_texture(*line, parse))
				break ;
		}
		else if (is_color(*line))
		{
			if (!extract_color(*line, parse))
				break ;
		}
		else if (!is_empty(*line))
		{
			break ;
		}
		free(*line);
		*line = get_next_line(fd_map);
	}
	result = final_asset_check(parse);
	return (result);
}
