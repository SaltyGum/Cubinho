/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 09:36:19 by dvargas           #+#    #+#             */
/*   Updated: 2023/04/19 12:30:47 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_cub3d.h"

void print_cubinho(void)
{
  printf("      ___           ___                                     ___           ___           ___     \n");
  printf("     /\\__\\         /\\  \\         _____                     /\\  \\         /\\  \\         /\\  \\    \n");
  printf("    /:/  /         \\:\\  \\       /::\\  \\       ___          \\:\\  \\        \\:\\  \\       /::\\  \\   \n");
  printf("   /:/  /           \\:\\  \\     /:/\\:\\  \\     /\\__\\          \\:\\  \\        \\:\\  \\     /:/\\:\\  \\  \n");
  printf("  /:/  /  ___   ___  \\:\\  \\   /:/ /::\\__\\   /:/__/      _____\\:\\  \\   ___ /::\\  \\   /:/  \\:\\  \\ \n");
  printf(" /:/__/  /\\__\\ /\\  \\  \\:\\__\\ /:/_/:/\\:|__| /::\\  \\     /::::::::\\__\\ /\\  /:/\\:\\__\\ /:/__/ \\:\\__\\\n");
  printf(" \\:\\  \\ /:/  / \\:\\  \\ /:/  / \\:\\/:/ /:/  / \\:\\:\\  \\__  \\:\\~~\\~~\\/__/ \\:\\/:/  \\/__/ \\:\\  \\ /:/  /\n");
  printf("  \\:\\  /:/  /   \\:\\  /:/  /   \\::/_/:/  /   \\:\\:\\/\\__\\  \\:\\  \\        \\::/__/       \\:\\  /:/  / \n");
  printf("   \\:\\/:/  /     \\:\\/:/  /     \\:\\/:/  /     \\:\\/:/  /   \\:\\__\\        \\:\\  \\        \\:\\/:/  /  \n");
  printf("    \\::/  /       \\::/  /       \\::/  /       \\::/  /     \\:\\__\\        \\:\\__\\        \\::/  /   \n");
  printf("     \\/__/         \\/__/         \\/__/         \\/__/       \\/__/         \\/__/         \\/__/    \n");
}


void help()
{
	print_cubinho();
	printf("\nWelcome to CUBINHO WORLD!\n\n");
	printf("Movement\n");
	printf("- W(up) S(down) A(left) D(right)\n");
	printf("- Left Arrow(camera left) Right Arrow(camera right)\n");
	printf("- ESC Exit the game in a clean way\n");
	printf("Good Luck and Have Fun!\n");
}

void help_error(void)
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