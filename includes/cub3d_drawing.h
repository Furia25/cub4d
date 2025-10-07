/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_drawing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 23:02:52 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/07 23:50:46 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_DRAWING_H
# define CUB3D_DRAWING_H
# include "crazypng.h"
# include "maths2_geometry.h"
# include "cub3d_structs.h"

void	draw_pixel(t_rgba8 rgba, unsigned int x,
			unsigned int y, t_img_data *img);
void	draw_spr_sheet(t_draw_transform tform, size_t index,
			t_sprite_sheet *sprite, t_img_data *img);
void	draw_rectangle(t_svec2 pos, t_svec2 size,
			t_rgba8 color, t_img_data *frame);

#endif