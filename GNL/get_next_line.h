/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeluiz4 <jeffluiz97@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 23:49:56 by jeluiz4           #+#    #+#             */
/*   Updated: 2022/06/16 00:01:16 by jeluiz4          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

char				*get_next_line(int fd);
size_t				ft_strlen(char *str);
char				*ft_substr(int start, char *str, size_t end);
char				*ft_subfre(int start, char *str, size_t end);
char				*ft_strjoin(char *dest, char *src);
long int			ft_nseek(char *haystack);
char				*ft_memcpy(char *dest, char *src, size_t n);
char				*faklloc(char *str);
char				*get_line(char *wheel, int fd);

#endif
