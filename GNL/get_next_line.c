/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeluiz4 <jeffluiz97@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:18:22 by jeluiz4           #+#    #+#             */
/*   Updated: 2022/06/16 01:54:01 by jeluiz4          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"

char	*ft_substr(int start, char *str, size_t end)
{
	char	*cut;
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	if ((ft_strlen(str) + start) < end)
		end = ft_strlen(str) + start;
	cut = malloc(end + 1);
	if (!cut)
		return (NULL);
	while (i < end)
	{
		cut[i] = str[start];
		start++;
		i++;
	}
	cut[i] = '\0';
	return (cut);
}

char	*ft_subfre(int start, char *str, size_t end)
{
	char	*cut;
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	if ((ft_strlen(str) + start) < end)
		end = ft_strlen(str) + start;
	cut = malloc(end + 1);
	if (!cut)
		return (NULL);
	while (i < end)
	{
		cut[i] = str[start];
		start++;
		i++;
	}
	cut[i] = '\0';
	free(str);
	return (cut);
}

char	*ft_strjoin(char *dest, char *src)
{
	char	*str;
	size_t	dest_i;
	size_t	src_i;

	dest_i = 0;
	src_i = 0;
	if (!src || !dest)
		return (NULL);
	str = malloc(ft_strlen(dest) + ft_strlen(src) + 1);
	if (!str)
		return (NULL);
	while (dest[dest_i])
	{
		str[dest_i] = dest[dest_i];
		dest_i++;
	}
	while (src[src_i])
	{
		str[dest_i + src_i] = src[src_i];
		src_i++;
	}
	str[dest_i + src_i] = '\0';
	free(dest);
	return (str);
}

char	*doner(char **wheel)
{
	char			*str;
	long int		pos;

	pos = ft_nseek(*wheel);
	if (pos != -1)
	{
		str = ft_substr(0, *wheel, pos + 1);
		*wheel = ft_subfre(pos + 1, *wheel,
				ft_strlen(*wheel) - (pos + 1));
	}
	else
	{
		str = ft_substr(0, *wheel, ft_strlen(*wheel));
		free(*wheel);
		*wheel = NULL;
	}
	if (!*str)
	{
		free(str);
		return (NULL);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char				*wheel;
	char					*temp;

	if (fd < 0 || BUFFER_SIZE < 1)
	{
		if (wheel)
			free(wheel);
		return (NULL);
	}
	if (!wheel)
		wheel = faklloc(wheel);
	temp = get_line(wheel, fd);
	if (!temp)
	{
		free(temp);
		return (NULL);
	}
	wheel = temp;
	return (doner(&wheel));
}
/*
int main(void)
{
	int	fd;
	int	i = 0;
	char	*dope;

	fd = open("entry.txt", O_RDONLY);
	while (i < 15)
	{
		dope = ft_get_next_line(fd);
		printf("\n%d %s--", i, dope);
		free(dope);
		i++;
	}

	close(fd);
}*/
