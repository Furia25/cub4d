/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_drawing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 23:02:52 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/05 23:11:06 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_DRAWING_H
# define CUB3D_DRAWING_H
# include "crazypng.h"
# include "maths2_geometry.h"
# include "cub3d_structs.h"

void	img_draw_pixel(t_png_pixel8 rgba, int x, int y, t_img_data *img);
void	img_draw_rect(t_png_pixel8 rgba, t_rect rectangle, t_img_data *img);

static inline t_png_pixel8	rgba8(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return ((t_png_pixel8) {r, g, b, a});
}

#endif