/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 09:36:19 by dvargas           #+#    #+#             */
/*   Updated: 2023/04/22 08:13:33 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_cub3d.h"

void	print_cubinho(void)
{
	printf("      ___           ___                                     ___");
	printf("           ___           ___     \n");
	printf("     /\\__\\         /\\  \\         _____                  ");
	printf("   /\\  \\         /\\  \\         /\\  \\    \n");
	printf("    /:/  /         \\:\\  \\       /::\\  \\       ___         ");
	printf(" \\:\\  \\        \\:\\  \\       /::\\  \\   \n");
	printf("   /:/  /           \\:\\  \\     /:/\\:\\  \\     /\\__\\     ");
	printf("     \\:\\  \\        \\:\\  \\     /:/\\:\\  \\  \n");
	printf("  /:/  /  ___   ___  \\:\\  \\   /:/ /::\\__\\   /:/__/");
	printf("      _____\\:\\  \\   ___ /::\\  \\   /:/  \\:\\  \\ \n");
	printf(" /:/__/  /\\__\\ /\\  \\  \\:\\__\\ /:/_/:/\\:|__| /::\\  \\     ");
	printf("/::::::::\\__\\ /\\  /:/\\:\\__\\ /:/__/ \\:\\__\\\n");
	printf(" \\:\\  \\ /:/  / \\:\\  \\ /:/  / \\:\\/:/ /:/  / \\:\\:\\  \\__");
	printf("  \\:\\~~\\~~\\/__/ \\:\\/:/  \\/__/ \\:\\  \\ /:/  /\n");
	printf("  \\:\\  /:/  /   \\:\\  /:/  /   \\::/_/:/  /   \\:\\:\\/\\__");
	printf("\\  \\:\\  \\        \\::/__/       \\:\\  /:/  / \n");
	printf("   \\:\\/:/  /     \\:\\/:/  /     \\:\\/:/  /     \\:\\/:/  /");
	printf("   \\:\\__\\        \\:\\  \\        \\:\\/:/  /  \n");
	printf("    \\::/  /       \\::/  /       \\::/  /       \\::/  /     ");
	printf("\\:\\__\\        \\:\\__\\        \\::/  /   \n");
	printf("     \\/__/         \\/__/         \\/__/         \\/__/");
	printf("       \\/__/         \\/__/         \\/__/    \n");
}

void	help(void)
{
	print_cubinho();
	printf("\nWelcome to CUBINHO WORLD!\n\n");
	printf("Movement\n");
	printf("- W(up) S(down) A(left) D(right)\n");
	printf("- Left Arrow(camera left) Right Arrow(camera right)\n");
	printf("- ESC Exit the game in a clean way\n");
	printf("Good Luck and Have Fun!\n");
}

void	help_error(void)
{
	print_cubinho();
	printf("\nWelcome to CUBINHO WORLD!\n\n");
	printf("Here are the instructions to play:\n");
	printf("- You first need a .cub map containing 4 .XPM 64x64 \
			to indicate wall textures.\n");
	printf("- 2 RGB colors for the Floor and Ceiling.\n");
	printf("- A map contain only: 0, 1 and Player position.\n");
	printf("- 0 stands for floor, 1 stands for wall and Player \
			position should be N, S, W, E.\n");
	printf("- The map should not have open walls.\n");
	printf("- The map need to have a player.\n\n");
	printf("Run the game with map name as first argument -> ");
	printf("./cub3d maps/yourmap.cub\n\n");
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
	return ;
}
