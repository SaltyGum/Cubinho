/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_cub3d.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:51:19 by jeluiz4           #+#    #+#             */
/*   Updated: 2023/04/08 09:31:20 by dvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_CUB3D_H
# define LIB_CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "mlx_linux/mlx.h"
# include "libft/libft.h"
# include "lib_parse.h"
# include <X11/Xlib.h>

//BASIC
# define FALSE 0
# define TRUE 1

//MATH DEFINES
# define PI (3.14159265358)
# define TWO_PI (6.28318530)

//VIEW VALUE == 60 * (PI / 180.0)
# define FOV_ANGLE (1.04719755119)

// MAP
# define TILE_SIZE (32)

//WINDOW SIZE
# define WIDTH 2000.0
# define HEIGHT 800.0

//Ray
# define NB_OF_RAYS(WIDTH)

// BUTTONS SETUP
// ARROWS
# define ARROW_UP 65362
# define ARROW_DOWN 65364
# define ARROW_LEFT 65361
# define ARROW_RIGHT 65363
# define W 119
# define A 97
# define S 115
# define D 100

// SCROLLING
# define SCRL_UP 4
# define SCRL_DOWN 5

// COLOR CHANGE HELP PANEL AND RESET
# define C_BUT 99
# define R_BUT 114

//Color
# define RED_PIXEL 0xFF0000
# define WHITE_PIXEL 0xFEFEFE
# define DARK_PIXEL 0x000000
# define GREY_PIXEL 0x808080
# define PIXEL_NONE 0xFF000000

// WINDOW CLOSE
# define ESC_BUT 65307
# define WIN_X 17

typedef struct s_player
{
	float	x;
	float	y;
	float	width;
	float	height;
	float	rotation_angle;
	float	walk_speed;
	float	turn_speed;
	int		turn_direction;
	int		walk_direction;
	int		moved;

}				t_player;

typedef struct s_cub3d
{
	t_player player;
	t_parse	*map;
	char	*type;
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_cub3d;

typedef struct s_pos{
	double x;
	double y;
} t_pos;

//utils
void	my_mlx_pixelput(t_cub3d *data, int x, int y, int color);

//Init Functions
void	player_init(t_cub3d *blk, t_player *player);

//Control Functions
void key_listening(t_cub3d *blk);
int	clk_act(t_cub3d *blk);
int	ft_close(t_cub3d *blk);

//Math Functions
double	degtorad(double degrees);
double	radtodeg(double radius);

//Draw Functions
void	draw_rectangle(t_cub3d *game, int x, int y, int width, int height, int color);
void draw_line(t_cub3d *blk, int x0, int y0, int x1, int y1);

//Render Functions
void minimap_render(t_cub3d *blk);
int render(t_cub3d *blk);

//Move Functions
int move_player(t_cub3d *blk);


#endif
