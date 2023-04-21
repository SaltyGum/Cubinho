/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_cub3d.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvargas < dvargas@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:51:19 by jeluiz4           #+#    #+#             */
/*   Updated: 2023/04/19 23:27:26 by jeluiz4          ###   ########.fr       */
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

//TEXTURE
# define TEXTURE_HEIGHT 64
# define TEXTURE_WIDTH 64

// MAP
# define TILE_SIZE (64)

//WINDOW SIZE
# define WIDTH 1024
# define HEIGHT 720

# define MINIMAP_SCALE 0.2
//# define MINIMAP_SCALE2 0.5

//Ray
# define NB_OF_RAYS (WIDTH)

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

//rosa dos ventos
# define NO 0
# define SO 1
# define WE 2
# define EA 3

typedef struct s_img
{
	void	*img;
	int 	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_new_ray
{
	int		ray_face_down;
	int		ray_face_up;
	int		ray_face_right;
	int		ray_face_left;
	float	hor_xintercept;
	float	hor_yintercept;
	float	hor_xstep;
	float	hor_ystep;
	float	vert_xintercept;
	float	vert_yintercept;
	float	vert_xstep;
	float	vert_ystep;
	int		hor_wall_hit;
	float	hor_wall_hit_x;
	float	hor_wall_hit_y;
	float	next_hor_touch_x;
	float	next_hor_touch_y;
	float	hor_x_to_check;
	float	hor_y_to_check;
	float	vert_x_to_check;
	float	vert_y_to_check;
	int		vert_wall_hit;
	float	vert_wall_hit_x;
	float	vert_wall_hit_y;
	float	next_vert_touch_x;
	float	next_vert_touch_y;
	float	hor_hit_distance;
	float	ver_hit_distance;
}	t_new_ray;

typedef struct s_player
{
	int		strafe;
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

typedef struct s_projection
{
	float		perp_dist;
	float		dist_proj_plane;
	float		proj_wall_hei;
	float		wall_strip_height;
	float		wall_top_pix;
	float		wall_bot_pix;
	int			texture_offset_x;
	int			dist_from_top;
	int			texture_offset_y;
	u_int32_t	texel_color;
}				t_projection;

typedef struct s_ray
{
	float	ray_angle;
	float	hit_x_wall;
	float	hit_y_wall;
	float	distance;
	int		is_hit_vertical;
	int		is_ray_face_up;
	int		is_ray_face_down;
	int		is_ray_face_left;
	int		is_ray_face_right;
	int		hit_content;
}				t_ray;

typedef struct s_cub3d
{
	t_player player;
	t_parse	*map;
	t_ray	ray[NB_OF_RAYS];
	char	*type;
	void	*mlx;
	void	*win;
	t_img	game;
	t_img	minimap;
	t_img	textureimg[4];

}				t_cub3d;

typedef struct s_pos{
	double x;
	double y;
} t_pos;

void help(void);
void help_error(void);
void	init_textures(t_cub3d *blk);

//utils
void	my_mlx_pixelput(t_img *data, int x, int y, int color);

//Init Functions
void	player_init(t_cub3d *blk, t_player *player);

//Control Functions
void	key_listening(t_cub3d *blk);
int		clk_act(t_cub3d *blk);
int		ft_close(t_cub3d *blk);

//Math Functions
double	degtorad(double degrees);
double	radtodeg(double radius);
float	norm_angle(float angle);

//Draw Functions
void	draw_rectangle(t_cub3d *game, int x, int y, int width, int height, int color);
void	draw_line(t_img *img, t_pos wid, t_pos hei);
void	make_rectangle(t_img *game, t_pos pos[2], int color);
void	get_rect(t_cub3d *blk, int x, int y, int color);
void	draw_player(t_cub3d *blk);

//Render Functions
void	minimap_render(t_cub3d *blk);
int		render(t_cub3d *blk);

//Move Functions
int		move_player(t_cub3d *blk);
int	strafe(t_cub3d *blk, int x);
int	move_to_front(t_cub3d *blk);
int	move_to_back(t_cub3d *blk);
int	rotate_player(t_cub3d *blk);


//Ray
void	cast_rays(t_cub3d *blk);
void	cast_one_ray(t_cub3d *blk, float ray_angle, int ray_id);

//Ray operations
void	find_vert_hit(t_cub3d *blk, t_new_ray *nray);
void	find_hor_hit(t_cub3d *blk, t_new_ray *nray);
void	set_vert_step(t_cub3d *blk, t_new_ray *nray, float ray_angle);
void	set_hor_step(t_cub3d *blk, t_new_ray *nray, float ray_angle);
void	nray_init(t_new_ray *ray, float ray_angle);

int	is_a_wall(t_cub3d *blk, float x, float y);
float	points_distance(float x1, float y1, float x2, float y2);

//Projection Functions
void	generate3d_projection(t_cub3d *blk);

void	init_projection(t_cub3d *blk, t_projection *prj, int i);
void	set_x_offset(t_cub3d *blk, t_projection *proj, int i);
void	put_texture(t_cub3d *blk, t_projection *proj, t_pos pos, int size);
void	set_y_offset(t_projection *proj, int y);

#endif
