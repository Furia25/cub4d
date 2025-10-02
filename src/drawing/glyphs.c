/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glyphs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:42:38 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/02 15:35:03 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glyphs.h"

static t_sprite	g_glyphs = {0};

bool	glyph_init(char *asset)
{
	g_glyphs.sheet.width = GLYPH_SIZE;
	g_glyphs.sheet.height = GLYPH_SIZE;
	g_glyphs.sheet.spr_per_line = 16;
	g_glyphs.sheet.asset = png_open(asset);
	return (g_glyphs.sheet.asset != NULL);
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

void	draw_glyph(t_text_context *ctx, size_t glyph, t_render_context *render)
{
	t_transform	temp;

	temp = ctx->tform;
	temp.index = glyph;
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
		draw_sprite(temp, &g_glyphs, render);
		if (ctx->effect & TE_BOLD)
		{
			temp.x += temp.width * 0.07;
			temp.y -= temp.height * 0.07;
			draw_sprite(temp, &g_glyphs, render);
		}
	}
}

void	glyph_end(void)
{
	png_close(g_glyphs.sheet.asset);
}
