/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 23:03:57 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/16 19:03:32 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H
# include <X11/keysym.h>
# include <X11/Xlib.h>
# include <stdint.h>
# include <crazypng.h>

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
	KEY_TEST_RIGHT,
	KEY_TEST_LEFT,
	KEY_MAX_COUNT
}	t_key_type;

static const int	g_keymap[KEY_MAX_COUNT] = {
[KEY_QUIT] = XK_Escape,
[KEY_TEST] = XK_e,
[KEY_UP] = XK_w,
[KEY_DOWN] = XK_s,
[KEY_LEFT] = XK_a,
[KEY_RIGHT] = XK_d,
[KEY_JUMP] = XK_space,
[KEY_TEST_LEFT] = XK_Left,
[KEY_TEST_RIGHT] = XK_Right,
[KEY_TEST_DOWN] = XK_Down,
[KEY_TEST_UP] = XK_Up,
};

typedef struct s_key
{
	uint64_t		time;
	t_key_type		type;
	bool			pressed;
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

typedef t_png_pixel8	t_rgba8;

#endif