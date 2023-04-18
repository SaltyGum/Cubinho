/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:00:28 by jeluiz4           #+#    #+#             */
/*   Updated: 2023/04/18 08:28:00 by jeluiz4          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_cub3d.h"

void	print_player_status(t_cub3d *blk)
{
	printf("Vlor de X:%f\n", blk->player.x);
	printf("Vlor de Y:%f\n", blk->player.y);
	printf("Vlor de rotation:%f\n", blk->player.rotation_angle);
	printf("Vlor de direction:%d\n", blk->player.turn_direction);
}

int	key_press_handle(int key, t_cub3d *blk)
{
	if (key == ESC_BUT)
		ft_close(blk);
	else if (key == ARROW_UP || key == W)
		blk->player.walk_direction += 1;
	else if (key == ARROW_DOWN || key == S)
		blk->player.walk_direction -= 1;
	else if (key == ARROW_RIGHT)
		blk->player.turn_direction += 1;
	else if (key == ARROW_LEFT)
		blk->player.turn_direction -= 1;
	else if (key == A)
		blk->player.walk_direction += 2;
	else if (key == D)
		blk->player.walk_direction -= 2;
	return (0);
}

int	key_release_handle(int key, t_cub3d *blk)
{
	if (key == ESC_BUT)
		ft_close(blk);
	else if ((key == ARROW_UP || key == W)
		&& blk->player.walk_direction == 1)
		blk->player.walk_direction = 0;
	else if ((key == ARROW_DOWN || key == S)
		&& blk->player.walk_direction == -1)
		blk->player.walk_direction = 0;
	else if (key == ARROW_LEFT)
		blk->player.turn_direction = 0;
	else if (key == ARROW_RIGHT)
		blk->player.turn_direction = 0;
	else if (key == A)
		blk->player.walk_direction = 0;
	else if (key == D)
		blk->player.walk_direction = 0;
	return (0);
}

int	move_player(t_cub3d *blk)
{
	int	move;

	move = 0;
	if (blk->player.turn_direction != 0)
		move += rotate_player(blk);
	if (blk->player.walk_direction == 1)
		move += move_to_front(blk);
	if (blk->player.walk_direction == -1)
		move += move_to_back(blk);
	if (blk->player.walk_direction == 2)
		move += strafe(blk, -1);
	if (blk->player.walk_direction == -2)
		move += strafe(blk, 1);
	return (move);
}

void	key_listening(t_cub3d *blk)
{
	mlx_hook(blk->win, WIN_X, 0, &ft_close, blk);
	mlx_hook(blk->win, KeyPress, KeyPressMask, key_press_handle, blk);
	mlx_hook(blk->win, KeyRelease, KeyReleaseMask, &key_release_handle, blk);
}
