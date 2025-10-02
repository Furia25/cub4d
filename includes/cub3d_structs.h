/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 23:03:57 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/02 12:37:34 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H
# include <X11/keysym.h>
# include <X11/Xlib.h>
# include <stdint.h>
# include <crazypng.h>
# include "maths2_vectors.h"

typedef union u_rgba8
{
	t_png_pixel8	channels;
	uint32_t		integer;
}	t_rgba8;

typedef enum e_key_type
{
	KEY_QUIT,
	KEY_TEST,
	KEY_FLY_UP,
	KEY_FLY_DOWN,
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_JUMP,
	KEY_TAB,
	KEY_LOOK_RIGHT,
	KEY_GRAVITY,
	KEY_LOOK_LEFT,
	KEY_INTERACT,
	KEY_ENTER,
	KEY_PAUSE,
	KEY_FLEX,
	KEY_MAX_COUNT
}	t_key_type;

extern const int	g_keymap[KEY_MAX_COUNT];

typedef struct s_key
{
	uint64_t		time;
	t_key_type		type;
	bool			pressed;
	bool			pressed_once;
	bool			released_once;
}	t_key;

typedef struct s_img_data
{
	void	*connection;
	void	*img_ptr;
	char	*buffer;
	int		width;
	int		height;
	int		pbits;
	int		size_line;
	int		endian;
}	t_img_data;

typedef struct s_sprite_sheet
{
	t_png	*asset;
	size_t	width;
	size_t	height;
	size_t	spr_per_line;
}	t_sprite_sheet;

typedef struct s_draw_transform
{
	size_t	x;
	size_t	y;
	size_t	width;
	size_t	height;
	t_rgba8	color;
}	t_draw_transform;

typedef struct s_transform
{
	int		x;
	int		y;
	int		width;
	int		height;
	float	depth;
	size_t	index;
	float	scale;
	t_rgba8	color;
}	t_transform;

typedef struct s_sprite
{
	t_sprite_sheet		sheet;
	t_transform			transform;
}	t_sprite;

typedef struct s_player
{
	t_vec3	spawn_pos;
	float	base_speed;
	float	eye_height;
	float	jump_force;
	float	fov_deg;
	float	accel_speed;
	float	accel_max;
	float	friction;
	t_bbox	bbox;
	t_vec3	position;
	t_vec2	direction;
	float	yaw_rad;
	int		pitch_offset;
	float	accel;
	float	jump_velocity;
	t_vec2	last_move;
	bool	is_grounded;
	bool	has_gravity;
}	t_player;

#endif