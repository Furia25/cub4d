/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 23:03:57 by vdurand           #+#    #+#             */
/*   Updated: 2025/07/04 18:42:53 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H
# include <X11/keysym.h>
# include <X11/Xlib.h>
# include <stdint.h>
# include <crazypng.h>

typedef t_png_pixel8	t_rgba8;

typedef enum e_key_type
{
	KEY_QUIT,
	KEY_TEST,
	KEY_TEST_UP,
	KEY_TEST_DOWN,
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_JUMP,
	KEY_TAB,
	KEY_TEST_RIGHT,
	KEY_TEST_LEFT,
	KEY_INTERACT,
	KEY_ENTER,
	KEY_PAUSE,
	KEY_MAX_COUNT
}	t_key_type;

static const int	g_keymap[KEY_MAX_COUNT] = {
[KEY_QUIT] = XK_Escape,
[KEY_TEST] = XK_r,
[KEY_UP] = XK_w,
[KEY_DOWN] = XK_s,
[KEY_LEFT] = XK_a,
[KEY_RIGHT] = XK_d,
[KEY_JUMP] = XK_space,
[KEY_TAB] = XK_Tab,
[KEY_TEST_LEFT] = XK_Left,
[KEY_TEST_RIGHT] = XK_Right,
[KEY_TEST_DOWN] = XK_Down,
[KEY_TEST_UP] = XK_Up,
[KEY_INTERACT] = XK_e,
[KEY_PAUSE] = XK_F1,
[KEY_ENTER] = XK_Return
};

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
    void		*connection;
    void		*img_ptr;
    char		*buffer;
    int			width;
    int			height;
    int			pbits;
    int			size_line;
    int			endian;
}	t_img_data;

typedef struct s_sprite_sheet
{
	t_png	*asset;
	size_t	width;
	size_t	height;
	size_t	sprite_per_line;
}	t_sprite_sheet;

typedef struct s_draw_transform
{
	size_t	x;
	size_t	y;
	size_t	width;
	size_t	height;
	t_rgba8	color;
}	t_draw_transform;

#endif