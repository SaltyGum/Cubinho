/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:50:32 by jeluiz4           #+#    #+#             */
/*   Updated: 2023/04/21 20:21:07 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_cub3d.h"
#include "lib_parse.h"

int	loop_render(t_cub3d *blk)
{
	blk->player.moved += move_player(blk);
	if (blk->player.moved == 0)
		return (0);
	cast_rays(blk);
	generate3d_projection(blk);
	minimap_render(blk);
	return (0);
}

void	set_minimap_size(t_cub3d *blk)
{
	int	i;
	int	side;

	if (blk->map->map.width > blk->map->map.height)
		side = blk->map->map.width;
	else
		side = blk->map->map.height;
	i = 0;
	while (side > 10)
	{
		side = side / 2;
		i++;
	}
	blk->scale = i;
	printf("i = %d \n \n ", blk->scale);
	return ;
}

void	init_mlx_imgs(t_cub3d *blk)
{
	int	map_x;
	int	map_y;

	set_minimap_size(blk);
	map_x = (blk->map->map.width * TILE_SIZE * MINIMAP_SCALE) / blk->scale + 11;
	map_y = (blk->map->map.height * TILE_SIZE * MINIMAP_SCALE)
		/ blk->scale + 11;
	blk->mlx = mlx_init();
	blk->win = mlx_new_window(blk->mlx, WIDTH, HEIGHT, "CUB3D");
	blk->game.img = mlx_new_image(blk->mlx, WIDTH, HEIGHT);
	blk->game.addr = (int *) mlx_get_data_addr(blk->game.img,
			&blk->game.bits_per_pixel,
			&blk->game.line_length, &blk->game.endian);
	blk->minimap.img = mlx_new_image(blk->mlx, map_x, map_y);
	blk->minimap.addr = (int *) mlx_get_data_addr(blk->minimap.img,
			&blk->minimap.bits_per_pixel, &blk->minimap.line_length,
			&blk->minimap.endian);
}

int	main(int argc, char **argv)
{
	t_cub3d	blk;

	if (argc != 2)
		return (help_error(), 1);
	blk.map = parse_map(argv[1]);
	if (blk.map == NULL)
		return (help_error(), 1);
	else
		help();
	player_init(&blk, &blk.player);
	init_mlx_imgs(&blk);
	init_textures(&blk);
	key_listening(&blk);
	mlx_loop_hook(blk.mlx, &loop_render, &blk);
	mlx_loop(blk.mlx);
}
