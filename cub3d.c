/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeluiz4 <jeffluiz97@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:50:32 by jeluiz4           #+#    #+#             */
/*   Updated: 2023/02/13 13:21:12 by jeluiz4          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_cub3d.h"

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

int	main(void)
{
	t_cub3d	blk;

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
}
