/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeluiz4 <jeffluiz97@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 23:43:11 by jeluiz4           #+#    #+#             */
/*   Updated: 2022/06/16 00:03:03 by jeluiz4          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

long int	ft_nseek(char *haystack)
{
	long int	i;
	long int	len;

	i = 0;
	len = ft_strlen(haystack);
	while (i <= len)
	{
		if (haystack[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_memcpy(char *dest, char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (n-- > 0)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

char	*faklloc(char *str)
{
	str = malloc(1);
	if (!str)
		return (NULL);
	str[0] = 0;
	return (str);
}

char	*get_line(char *wheel, int fd)
{
	long int	track;
	char		*temp;

	track = 1;
	temp = malloc(BUFFER_SIZE + 1);
	while (track)
	{
		if (ft_nseek(wheel) != -1)
			break ;
		if (!temp)
			return (NULL);
		track = read(fd, temp, BUFFER_SIZE);
		if (track < 0)
		{
			free(temp);
			return (NULL);
		}
		temp[track] = '\0';
		wheel = ft_strjoin(wheel, temp);
	}
	free(temp);
	return (wheel);
}
