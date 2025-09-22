/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glyphs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:42:38 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/22 19:02:19 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glyphs.h"

static t_sprite_sheet	g_glyphs = {0};

bool	glyph_init(char *asset)
{
	g_glyphs.width = GLYPH_SIZE;
	g_glyphs.height = GLYPH_SIZE;
	g_glyphs.spr_per_line = 16;
	g_glyphs.asset = png_open(asset);
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

void	draw_glyph(t_text_context *ctx, size_t glyph, t_img_data *img)
{
	t_draw_transform temp;

	temp = ctx->tform;
	temp.y -= (temp.height * 0.75);
	temp.color = ctx->tform.color;
	ctx->tform.x += ctx->prop->x_spacing * ctx->tform.width;
	ctx->tform.y += ctx->prop->y_spacing * ctx->tform.height;
	if (ctx->effect & TE_WAVE)
		geffect_wave(ctx, &temp);
	if (ctx->effect & TE_RAINBOW)
		geffect_rainbow(ctx, &temp);
	if (!(ctx->effect & TE_TYPEWRITER) || geffect_typewrite(ctx))
	{
		draw_spr_sheet(temp, glyph, &g_glyphs, img);
		if (ctx->effect & TE_BOLD)
		{
			temp.x += temp.width * 0.07;
			temp.y -= temp.height * 0.07;
			draw_spr_sheet(temp, glyph, &g_glyphs, img);
		}
	}
}

void	glyph_end(void)
{
	png_close(g_glyphs.asset);
}
