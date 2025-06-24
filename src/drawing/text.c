/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:27:11 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/24 15:50:52 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glyphs.h"

void	draw_text(wchar_t *glyphs, t_transform tform,
			t_text_properties prop, t_img_data *img)
{
	t_text_context	ctx;

	ctx.origin_x = tform.x;
	ctx.origin_y = tform.y;
	ctx.line_char = 0;
	ctx.line_n = 0;
	while (glyphs && *glyphs)
	{
		if (*glyphs == '\n' || (*glyphs == ' ' && ctx.line_char >= prop.wrap_max))
		{
			ctx.line_char = 0;
			ctx.line_n++;
			tform.x = ctx.origin_x + ctx.line_n * prop.nl_spacing_x;
			tform.y = ctx.origin_y + ctx.line_n * prop.nl_spacing_y;
			if (*glyphs == '\n')
				glyphs++;
		}
		ctx.actual_glyph = glyph_get_index(*glyphs);
		if (ctx.actual_glyph != -1)
		{
			draw_glyph(&tform, ctx.actual_glyph, img);
			tform.x += prop.x_spacing;
			tform.y += prop.y_spacing;
		}
		ctx.line_char++;
		glyphs++;
	}
}
