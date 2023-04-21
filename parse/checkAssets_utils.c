/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkAssets_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:36:05 by dvargas           #+#    #+#             */
/*   Updated: 2023/04/21 20:16:57 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_cub3d.h"

void	clean_path(char *path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (!ft_isspace(path[i]))
			i++;
		else
			break ;
	}
	path[i] = '\0';
}

int	validade_color(char *color)
{
	char	**tmp;
	int		rgb[3];
	int		i;

	i = 0;
	tmp = ft_split(color, ',');
	if (!tmp)
		return (0);
	while (tmp[i])
		i++;
	if (i != 3)
		return (free_matrix((void **)tmp), 0);
	i = 0;
	while (i < 3)
	{
		rgb[i] = ft_atoi(tmp[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (free_matrix((void **)tmp), 0);
		i++;
	}
	return (free_matrix((void **)tmp), 1);
}

int	is_empty(char *line)
{
	if (ft_strlen(line) == 1 && line[0] == '\n')
		return (1);
	return (0);
}

int	final_asset_check(t_parse *parse)
{
	int	ret;

	ret = 0;
	if (parse->no_texture != NULL)
		ret++;
	if (parse->so_texture != NULL)
		ret++;
	if (parse->ea_texture != NULL)
		ret++;
	if (parse->we_texture != NULL)
		ret++;
	if (parse->floor != -1)
		ret++;
	if (parse->ceil != -1)
		ret++;
	if (ret == 6)
		return (1);
	else
		return (0);
}

int	can_save(t_parse *parse, char *path, int flag)
{
	int	fd;

	if (flag < 5)
	{
		fd = open(path, O_RDONLY);
		if (fd < 0)
			return (0);
		close(fd);
	}
	if (flag == 1 && parse->no_texture != NULL)
		return (0);
	else if (flag == 2 && parse->so_texture != NULL)
		return (0);
	else if (flag == 3 && parse->ea_texture != NULL)
		return (0);
	else if (flag == 4 && parse->we_texture != NULL)
		return (0);
	else if (flag == 5 && parse->floor != -1)
		return (0);
	else if (flag == 6 && parse->ceil != -1)
		return (0);
	else
		return (1);
}
