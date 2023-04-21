/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:50:32 by jeluiz4           #+#    #+#             */
/*   Updated: 2023/04/21 20:51:07 by dvargas          ###   ########.fr       */
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
