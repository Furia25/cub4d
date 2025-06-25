/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:27:11 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/25 02:15:35 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_colors.h"
#include "glyphs.h"

static inline bool	char_command(t_text_context *ctx,
			wchar_t **str, t_text_properties *prop, wchar_t c)
{
	bool	valid;

	(void)prop;
	valid = false;
	if (c >= L'1' && c <= L'9')
	{
		ctx->tform.width = GLYPH_SIZE * (c - L'0');
		ctx->tform.height = GLYPH_SIZE * (c - L'0');
		valid = true;
	}
	else if (c >= L'a' && c <= L'z')
	{
		ctx->tform.color = g_color_text[c - L'a' + 1];
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

void	draw_text(wchar_t *str, t_text_properties prop, t_img_data *img)
{
	t_text_context		ctx;
	t_draw_transform	*tform;

	tform = &ctx.tform;
	tform->color = g_colors[C_WHITE];
	tform->color_tint = 1;
	tform->width = GLYPH_SIZE;
	tform->height = GLYPH_SIZE;
	tform->x = prop.x;
	tform->y = prop.y + tform->height;
	ctx.tform_default = ctx.tform;
	ctx.origin_x = tform->x;
	ctx.origin_y = tform->y;
	ctx.line_char = 0;
	ctx.line_n = 0;
	while (str && *str)
	{
		if (*str == L'»' && !text_command(&ctx, &str, &prop))
			continue ;
		if (*str == '\n' || (*str == ' ' && ctx.line_char >= prop.wrap_max))
		{
			ctx.line_char = 0;
			ctx.line_n++;
			tform->x = ctx.origin_x + (ctx.line_n * prop.nl_spacing_x * tform->width);
			tform->y = ctx.origin_y + (ctx.line_n * prop.nl_spacing_y * tform->height);
			str++;
		}
		ctx.actual_glyph = glyph_get_index(*str);
		if (ctx.actual_glyph != -1)
		{
			draw_glyph(&ctx.tform, ctx.actual_glyph, img);
			tform->x += prop.x_spacing * tform->width;
			tform->y += prop.y_spacing * tform->height;
		}
		ctx.line_char++;
		str++;
	}
}
