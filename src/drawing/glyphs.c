/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_glyph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:42:38 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/24 15:34:27 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glyphs.h"

static t_sprite_sheet	g_glyphs = {0};

bool	glyph_init(char *asset)
{
	g_glyphs.asset = png_open(asset);
	g_glyphs.width = GLYPH_SIZE;
	g_glyphs.height = GLYPH_SIZE;
	g_glyphs.sprite_per_line = 16;
	return (g_glyphs.asset != NULL);
}

ssize_t	glyph_get_index(wchar_t glyph)
{
	size_t			index;

	index = 0;
	while (GLYPHS[index])
	{
		if (GLYPHS[index] == glyph)
			return (index);
		index++;
	}
	return (-1);
}

void	draw_glyph(t_transform *tform, size_t index, t_img_data *img)
{
	draw_sprite_sheet(*tform, index, &g_glyphs, img);
}

void	glyph_end(void)
{
	png_close(g_glyphs.asset);
}
