/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:50:32 by jeluiz4           #+#    #+#             */
/*   Updated: 2023/04/12 21:14:28 by dvargas          ###   ########.fr       */
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
	t_cub3d	*blk;

	blk = malloc(sizeof(t_cub3d) * 1);
	if (!blk)
		return (1);
			blk->map = parse_map(argv[1]);
	if (blk->map == NULL)
		return (printf("Algo deu errado no caminho meu chapa\n\n"), 1);
	player_init(blk, &blk->player);
	if (argc != 2)
		return (ft_error("Wrong number of arguments"), 1);
	ft_printf("Parabens, o mapa e valido, vamos brincar\n");
	blk->mlx = mlx_init();
	blk->win = mlx_new_window(blk->mlx, WIDTH, HEIGHT, "CUB3D");
	blk->img = mlx_new_image(blk->mlx, WIDTH, HEIGHT);
	blk->addr = mlx_get_data_addr(blk->img,
			&blk->bits_per_pixel, &blk->line_length, &blk->endian);
	blk->player.moved = 1;
	//loop_render(blk);
	key_listening(blk);
	//mlx_mouse_hook(blk->win, &clk_act, blk);
	mlx_loop_hook(blk->mlx, &loop_render, blk);
	mlx_loop(blk->mlx);
}
