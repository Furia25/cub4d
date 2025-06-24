/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_glyph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:42:38 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/24 03:54:13 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_drawing.h"
#include "cub3d_textures.h"

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

/*TEMPTEMP*//**
 * @brief Renders a wide-character string onto an image using a glyph sprite sheet.
 *
 * This function draws text composed of glyphs onto a 2D image buffer. It takes into
 * account text layout properties such as character spacing, line spacing, and word wrapping.
 * Glyphs are retrieved from a sprite sheet and positioned based on the initial transform.
 *
 * Line breaks are triggered when:
 * - A newline character (`\n`) is encountered.
 * - The number of characters on the current line exceeds the wrapping limit (`wrap_max`).
 *
 * The drawing position is updated for each character based on spacing values.
 *
 * @param glyphs
 *   A null-terminated wide-character string to be rendered.
 *
 * @param tform
 *   A transform structure defining the starting position (`x`, `y`) where text rendering begins.
 *   Only the `x` and `y` fields are used to set the origin. The `width` and `height` fields
 *   represents the size of each glyph
 *
 * @param prop
 *   A structure defining spacing and wrapping behavior for the text layout.
 *
 * @param img
 *   A pointer to the image buffer where glyphs will be drawn.
 *
 * @note
 * - Characters not recognized by `glyph_get_index` are skipped (i.e., not rendered).
 * - Text rendering starts at `tform.x`, `tform.y` and moves from left to right,
 *   top to bottom, based on spacing and wrapping parameters.
 * - Manual newline characters (`\n`) will reset line position regardless of character count.
 */
void	glyph_draw_text(wchar_t *glyphs, t_transform tform,
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
			draw_sprite_sheet(tform, ctx.actual_glyph, &g_glyphs, img);
			tform.x += prop.x_spacing;
			tform.y += prop.y_spacing;
		}
		ctx.line_char++;
		glyphs++;
	}
}

void	glyph_end(void)
{
	png_close(g_glyphs.asset);
}
