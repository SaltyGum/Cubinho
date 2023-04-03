/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:50:32 by jeluiz4           #+#    #+#             */
/*   Updated: 2023/04/02 09:11:27 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_cub3d.h"
#include "lib_parse.h"

int	ft_close(t_cub3d *blk)
{
	if (blk->img)
		mlx_destroy_image(blk->mlx, blk->img);
	if (blk->mlx && blk->win)
	{
		mlx_destroy_window(blk->mlx, blk->win);
		free(blk->mlx);
	}
	printf("END\n");
	exit(42);
}

int	main(int argc, char **argv)
{
	t_cub3d	blk;
	t_parse	*parse;

	if (argc != 2)
		return (ft_error("Wrong number of arguments"), 1);
	parse = parse_map(argv[1]);
	if (parse == NULL)
		return (printf("Algo deu errado no caminho meu chapa\n\n"), 1);
	ft_printf("Parabens, o mapa e valido, vamos brincar\n");
	free_parse(parse);
	return(0);
	/*
	blk.mlx = mlx_init();
	blk.win = mlx_new_window(blk.mlx, WIDTH, HEIGHT, "CUB3D");
	//ft_help(); Caso queira colocar um help pro usuario
	blk.img = mlx_new_image(blk.mlx, WIDTH, HEIGHT);
	blk.addr = mlx_get_data_addr(blk.img, &blk.bits_per_pixel, &blk.line_length,
			&blk.endian);
	mlx_put_image_to_window(blk.mlx, blk.win, blk.img, 0, 0);
	mlx_hook(blk.win, WIN_X, 0, &ft_close, &blk);
	mlx_key_hook(blk.win, &ch_ose, &blk);
	mlx_mouse_hook(blk.win, &clk_act, &blk);
	mlx_loop(blk.mlx);
	*/
}
