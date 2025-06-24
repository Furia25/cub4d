/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glyphs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:31:44 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/24 15:55:14 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLYPHS_H
# define GLYPHS_H

# include "cub3d_drawing.h"
# include "cub3d_textures.h"
# include "maths2_utils.h"

# define GLYPH_SIZE		12
# define FONT_SIZE1		12
# define FONT_SIZE2		24
# define FONT_SIZE3		36
# define FONT_SIZE4		48
# define FONT_SIZE5		60
# define FONT_SIZE6		72
# define FONT_SIZE7		84
# define FONT_SIZE8		96
# define FONT_SIZE9		108
# define FONT_SIZE10	120

# define GLYPHS	L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefgh\
ijklmnopqrstuvwxyz0123456789.,?!:;`'\"*-_~#&|@≈[]<>\
{}()/\\+=^÷٪ $°·˗■□☰√ⁿ²∓≥≤⌈⌋▸☺☻♥♦♣♠◦◘○◙♂♀♪♫¤➜◂‼¶§\
▂↕↗↑↓→←↔★▴▾🔍❌☐☑"

typedef struct s_text_properties
{
	unsigned short	x_spacing;
	unsigned short	y_spacing;
	unsigned short	nl_spacing_x;
	unsigned short	nl_spacing_y;
	unsigned short	wrap_max;
}	t_text_properties;

typedef struct s_text_context
{
	size_t			origin_x;
	size_t			origin_y;
	ssize_t			actual_glyph;
	unsigned short	line_n;
	unsigned short	line_char;
}	t_text_context;

bool	glyph_init(char *asset);
void	glyph_end(void);
void	draw_text(wchar_t *glyphs, t_transform tform,
			t_text_properties prop, t_img_data *img);
void	draw_glyph(t_transform *tform, size_t index, t_img_data *img);
ssize_t	glyph_get_index(wchar_t glyph);
#endif