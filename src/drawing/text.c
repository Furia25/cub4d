/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:27:11 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/24 17:24:19 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glyphs.h"

static inline bool	char_command(t_text_context *ctx,
			wchar_t **str, t_text_properties *prop, wchar_t c)
{
	bool	valid;

	(void)prop;
	valid = false;
	if (c >= '1' && c <= '9')
	{
		ctx->tform->width = GLYPH_SIZE * (c - L'0');
		ctx->tform->height = GLYPH_SIZE * (c - L'0');
		valid = true;
	}
	if (valid)
		(*str)++;
	return (valid);
}

static inline bool	text_command(t_text_context *ctx,
			wchar_t **str, t_text_properties *prop)
{
	wchar_t	c;

	(void)prop;
	(*str)++;
	while (*str && **str)
	{
		c = **str;
		if (c == L'«')
			return (true);
		if (!char_command(ctx, str, prop, c))
			return (true);
	}
	return (false);
}

void	draw_text(wchar_t *str, t_transform tform,
			t_text_properties prop, t_img_data *img)
{
	t_text_context	ctx;

	tform.y += tform.height;
	ctx.origin_x = tform.x;
	ctx.origin_y = tform.y;
	ctx.line_char = 0;
	ctx.line_n = 0;
	ctx.tform = &tform;
	while (str && *str)
	{
		if (*str == L'»' && !text_command(&ctx, &str, &prop))
			continue ;
		if (*str == '\n' || (*str == ' ' && ctx.line_char >= prop.wrap_max))
		{
			ctx.line_char = 0;
			ctx.line_n++;
			tform.x = ctx.origin_x + ctx.line_n * prop.nl_spacing_x;
			tform.y = ctx.origin_y + ctx.line_n * prop.nl_spacing_y;
			str++;
		}
		ctx.actual_glyph = glyph_get_index(*str);
		if (ctx.actual_glyph != -1)
		{
			draw_glyph(&tform, ctx.actual_glyph, img);
			tform.x += prop.x_spacing * tform.width;
			tform.y += prop.y_spacing * tform.height;
		}
		ctx.line_char++;
		str++;
	}
}
