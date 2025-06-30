/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glyphs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:31:44 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/30 10:02:48 by halnuma          ###   ########.fr       */
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

/*TEMP TEMP Super long en runtime ça doit
 check pour chaque char : faire une lookup table ?*/
# define GLYPHS	L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefgh\
ijklmnopqrstuvwxyz0123456789.,?!:;`'\"*-_~#&|@≈[]<>\
{}()/\\+=^÷٪ $°·˗■□☰√ⁿ²∓≥≤⌈⌋▸☺☻♥♦♣♠◦◘○◙♂♀♪♫¤➜◂‼¶§\
▂↕↗↑↓→←↔★▴▾🔍❌☐☑\0"

typedef struct s_text_properties
{
	size_t			x;
	size_t			y;
	float			x_spacing;
	float			y_spacing;
	float			nl_spacing_x;
	float			nl_spacing_y;
	unsigned short	wrap_max;
	uint64_t		start_time;
}	t_text_properties;

typedef enum e_text_effect
{
	TE_TYPEWRITER = 1 << 0,
	TE_WAVE = 1 << 1,
	TE_RAINBOW = 1 << 2,
	TE_BOLD = 1 << 3,
	TE_EMPTY = 0,
	TE_ALL = TE_TYPEWRITER | TE_WAVE | TE_RAINBOW
}	t_text_effect;

typedef struct s_text_context
{
	size_t				index;
	size_t				length;
	size_t				nl_x;
	size_t				nl_y;
	ssize_t				actual_glyph;
	unsigned short		line_n;
	unsigned short		line_char;
	t_draw_transform	tform;
	bool				true_break;
	uint8_t				effect;
	uint64_t			start_time;
	t_text_properties	*prop;
}	t_text_context;

static const t_rgba8	g_color_text[26] = {
{.r = 0, .g = 0, .b = 0, .a = 255},
{.r = 255, .g = 255, .b = 255, .a = 255},
{.r = 255, .g = 0, .b = 0, .a = 255},
{.r = 0, .g = 255, .b = 0, .a = 255},	
{.r = 0, .g = 0, .b = 255, .a = 255},
{.r = 0, .g = 255, .b = 255, .a = 255},
{.r = 255, .g = 255, .b = 0, .a = 255},
{.r = 255, .g = 0, .b = 255, .a = 255},
{.r = 255, .g = 165, .b = 0, .a = 255},
{.r = 128, .g = 0, .b = 128, .a = 255},
{.r = 255, .g = 192, .b = 203, .a = 255},
{.r = 165, .g = 42, .b = 42, .a = 255},
{.r = 128, .g = 128, .b = 128, .a = 255},
{.r = 211, .g = 211, .b = 211, .a = 255},
{.r = 169, .g = 169, .b = 169, .a = 255},
{.r = 0, .g = 0, .b = 128, .a = 255},
{.r = 128, .g = 128, .b = 0, .a = 255},
{.r = 0, .g = 255, .b = 0, .a = 255},
{.r = 0, .g = 128, .b = 128, .a = 255},
{.r = 0, .g = 255, .b = 255, .a = 255},
{.r = 128, .g = 0, .b = 0, .a = 255},
{.r = 192, .g = 192, .b = 192, .a = 255},
{.r = 255, .g = 215, .b = 0, .a = 255},
{.r = 255, .g = 127, .b = 80, .a = 255},
{.r = 250, .g = 128, .b = 114, .a = 255},
{.r = 210, .g = 105, .b = 30, .a = 255}
};

bool	glyph_init(char *asset);
void	glyph_end(void);

void	draw_text(wchar_t *glyphs, t_text_properties prop, t_img_data *img);
void	draw_glyph(t_text_context *ctx, size_t index, t_img_data *img);

ssize_t	glyph_get_index(wchar_t glyph);
size_t	strlen_wchar(wchar_t *str);

bool	geffect_typewrite(t_text_context *ctx);
void	geffect_wave(t_text_context *ctx, t_draw_transform *temp);
void	geffect_rainbow(t_text_context *ctx, t_draw_transform *temp);
#endif
