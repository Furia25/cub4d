/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_glyph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:42:38 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/23 18:13:04 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_drawing.h"

static t_png	*g_glyph_png = {NULL};

bool	init_glyph(char *asset)
{
	g_glyph_png = png_open(asset);
	return (g_glyph_png);
}

void	draw_glyph(int x, int y, size_t glyph, t_img_data *img)
{
	
}

void	end_glyph(void)
{
	png_close(g_glyph_png);
}
