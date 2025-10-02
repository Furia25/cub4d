/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:27:11 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/02 15:30:02 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"
#include "glyphs.h"

static inline bool	char_command(t_text_context *ctx, char c)
{
	bool	valid;

	valid = true;
	if (c >= L'1' && c <= L'9')
	{
		ctx->tform.width = GLYPH_SIZE * (c - L'0');
		ctx->tform.height = GLYPH_SIZE * (c - L'0');
	}
	else if (c >= L'a' && c <= L'z')
		ctx->tform.color = g_color_text[c - L'a'];
	else if (c == '#')
		ctx->true_break = true;
	else if (c == '~')
		ctx->effect = ctx->effect ^ TE_WAVE;
	else if (c == 'T')
		ctx->effect = ctx->effect ^ TE_TYPEWRITER;
	else if (c == L'=')
		ctx->effect = ctx->effect ^ TE_RAINBOW;
	else if (c == L'*')
		ctx->effect = ctx->effect ^ TE_BOLD;
	else if (c == L'_')
		ctx->effect = TE_EMPTY;
	else
		valid = false;
	ctx->index += valid;
	return (valid);
}

static inline bool	text_command(t_text_context *ctx, char *str)
{
	wchar_t	c;

	ctx->index++;
	while (str[ctx->index])
	{
		c = str[ctx->index];
		if (c == L'}')
		{
			ctx->index++;
			return (true);
		}
		if (!char_command(ctx, c))
			return (true);
	}
	return (false);
}

static inline void	init_text(t_text_context *ctx, t_transform *tform,
						t_text_properties *prop, char *str)
{
	ft_memset(ctx, 0, sizeof(t_text_context));
	tform->depth = -2;
	tform->scale = 1;
	ctx->prop = prop;
	ctx->start_time = prop->start_time;
	ctx->length = ft_strlen(str);
	tform->color = g_colors[C_WHITE];
	tform->width = GLYPH_SIZE;
	tform->height = GLYPH_SIZE;
	tform->x = prop->x;
	tform->y = prop->y;
	prop->y += tform->height;
}

static inline void	line_break(t_text_context *ctx, t_text_properties *prop,
						t_transform *tform)
{
	ctx->line_char = 0;
	ctx->line_n++;
	ctx->nl_x += prop->nl_spacing_x * tform->width;
	ctx->nl_y += prop->nl_spacing_y * tform->height;
	tform->x = prop->x + ctx->nl_x;
	tform->y = prop->y + ctx->nl_y;
	ctx->index++;
}

void	draw_text(char *str, t_text_properties prop, t_render_context *render)
{
	t_text_context	ctx;
	t_transform		*tform;
	char			c;

	tform = &ctx.tform;
	init_text(&ctx, tform, &prop, str);
	while (str[ctx.index])
	{
		c = str[ctx.index];
		if (c == L'{' && text_command(&ctx, str))
			continue ;
		if (c == '\n' || (ctx.line_char >= prop.wrap_max
				&& (c == ' ' || ctx.true_break)))
		{
			line_break(&ctx, &prop, tform);
			continue ;
		}
		ctx.actual_glyph = glyph_get_index(c);
		if (ctx.actual_glyph != -1)
			draw_glyph(&ctx, ctx.actual_glyph, render);
		ctx.line_char++;
		ctx.index++;
	}
}
