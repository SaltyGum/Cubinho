/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:50:32 by jeluiz4           #+#    #+#             */
/*   Updated: 2023/04/19 23:53:02 by jeluiz4          ###   ########.fr       */
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

int find_gcf(int a, int b)
{
	int temp;
	while (b != 0)
	{
		temp = b;
		b = a % b;
		a = temp;
	}
	return (a);
}

void	rationalize(t_cub3d *blk, int *x, int *y)
{
	int	vet;
	int	hor;

	vet = (blk->map->map.width / blk->ratio) * 1.1;
	hor = (blk->map->map.width / blk->ratio) * 1.1;
	while (vet <= 350 && hor <= 200)
	{

		vet += (blk->map->map.width / blk->ratio) * 1.1;
		hor += (blk->map->map.width / blk->ratio) * 1.1;
	}
	*x = hor;
	*y = vet;
}

void	init_mlx_imgs(t_cub3d *blk)
{
	int	map_x;
	int	map_y;

	map_x = 0;
	map_y = 0;
	blk->ratio = find_gcf(blk->map->map.width, blk->map->map.height);
	rationalize(blk, &map_x, &map_y);
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
	help();
	blk.map = parse_map(argv[1]);
	if (blk.map == NULL)
		return (help_error(), 1);
	player_init(&blk, &blk.player);
	init_mlx_imgs(&blk);
	init_textures(&blk);
	key_listening(&blk);
	mlx_loop_hook(blk.mlx, &loop_render, &blk);
	mlx_loop(blk.mlx);
}
