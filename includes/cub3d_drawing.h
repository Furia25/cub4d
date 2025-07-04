/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_drawing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 23:02:52 by vdurand           #+#    #+#             */
/*   Updated: 2025/07/04 18:48:09 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_DRAWING_H
# define CUB3D_DRAWING_H
# include "crazypng.h"
# include "maths2_geometry.h"
# include "cub3d_structs.h"

/*TEMP*/
static inline t_rgba8	rgba8(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (t_rgba8){a, r, g, b};
}

void	draw_pixel(t_rgba8 rgba, unsigned int x, unsigned int y, t_img_data *img);
void	draw_rect(t_png_pixel8 rgba, t_rect rectangle, t_img_data *img);

#endif