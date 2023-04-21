/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_parse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 07:23:41 by dvargas           #+#    #+#             */
/*   Updated: 2023/04/21 20:42:54 by jeluiz4          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_PARSE_H
# define LIB_PARSE_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_map{
	char	**map;
	size_t	width;
	size_t	height;
	size_t	playerpositionx;
	size_t	playerpositiony;
	char	direction;
	int		tile_width;
	int		tile_height;
}	t_map;

typedef struct s_parse{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;

	int		floor;
	int		ceil;

	t_map	map;

}t_parse;

//funcoes de Ignite, Free e Error.
void	ft_error(char *error);
void	parse_ignite(t_parse *parse);
void	*free_parse(t_parse *parse);
void	free_map(t_map *map);
void	*free_matrix(void **matrix);
//Funcao Parse, ela e a principal
t_parse	*parse_map(char *path);
int		check_extension(char *str);
//funcoes de validacao dos assets
int		is_color(char *color);
int		is_texture(char *line);
int		extract_texture(char *line, t_parse *parse);
int		extract_color(char *line, t_parse *parse);
int		extract_assets(int fd_map, char **line, t_parse *parse);
//validate assets utils
int		validade_color(char *color);
int		can_save(t_parse *parse, char *path, int flag);
int		final_asset_check(t_parse *parse);
int		is_empty(char *line);
void	update_width_height(t_map *map);
//color handler
int		create_rgb(int r, int g, int b);
int		rgb_to_hex(char *color);
//Map Creation
char	**create_map(int fd, char **line);
char	*get_map_one_line(int fd_map, char **line);
//Map Creation - Utils
int		check_after_map(int fd, char **line);
int		check_map_char(char *line);
int		map_valid_line(char *line);
void	clean_path(char *path);
int		check_extension(char *str);
int		ft_str_search(char *str, char c);
int		set_map_width(char **map);
int		set_map_height(char **ret);
//Validate map
int		validate_map(t_parse parse);
t_map	*fill_map(t_parse parse);
int		map_is_open(t_map *map, size_t x, size_t y);
int		find_player(t_parse *parse, size_t x, size_t y, int ret);
//Validate map - utils
char	**map_xerox(t_parse parse);
char	**map_inside_box(t_map *map);
char	*fill_line_size(char *line, int size);

#endif
