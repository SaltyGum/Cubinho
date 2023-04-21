/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createMap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:31:32 by dvargas           #+#    #+#             */
/*   Updated: 2023/04/21 20:10:05 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_cub3d.h"

int	check_after_map(int fd, char **line)
{
	*line = get_next_line(fd);
	if (*line != NULL)
		return (0);
	return (1);
}

int	check_map_char(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!ft_str_search(" 10NSEW", line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	map_valid_line(char *line)
{
	if (!line)
		return (free(line), 0);
	if (!check_map_char(line))
		return (free(line), 0);
	else if (is_empty(line))
		return (free(line), 0);
	return (1);
}

char	*get_map_one_line(int fd_map, char **line)
{
	char	*ret;

	ret = ft_strdup("");
	while (*line != NULL)
	{
		if (!map_valid_line(*line))
			return (ft_error("Mapa errado 1 - mapValidLine"), free(ret), NULL);
		else
		{
			ft_swapjoin(&ret, *line);
			if (!ret)
				return (ft_error("swapJoin Error"), NULL);
		}
		free(*line);
		*line = get_next_line(fd_map);
	}
	return (ret);
}

char	**create_map(int fd, char **line)
{
	char	**ret;
	char	*map_one_line;

	map_one_line = get_map_one_line(fd, line);
	if (!map_one_line)
		return (NULL);
	ret = ft_split(map_one_line, '\n');
	free(map_one_line);
	return (ret);
}
