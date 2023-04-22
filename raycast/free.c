/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 09:16:56 by dvargas           #+#    #+#             */
/*   Updated: 2023/04/22 08:19:25 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_cub3d.h"

int	ft_close(t_cub3d *blk)
{
	if (blk->game.img != NULL)
		mlx_destroy_image(blk->mlx, blk->game.img);
	if (blk->minimap.img != NULL)
		mlx_destroy_image(blk->mlx, blk->minimap.img);
	if (blk->mlx && blk->win)
	{
		mlx_destroy_window(blk->mlx, blk->win);
		free(blk->mlx);
	}
	printf("END\n");
	exit(42);
}
