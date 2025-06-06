/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 23:03:57 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/05 23:31:55 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H
# include <X11/keysym.h>
# include <X11/Xlib.h>
# include <stdint.h>

typedef enum e_keymap
{
	KEY_QUIT = XK_Escape,
	KEY_TEST = XK_e,
	KEY_UP = XK_w,
	KEY_DOWN = XK_s,
	KEY_LEFT = XK_a,
	KEY_RIGHT = XK_d
}	t_keymap;

typedef struct s_key
{
	uint64_t	time;
	int			keycode;
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

#endif