/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_textures.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:20:57 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/24 03:53:47 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_TEXTURES_H
# define CUB3D_TEXTURES_H

# include "cub3d_structs.h"

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

typedef enum e_texture_type
{
	TEXTURE_NAN,
	TEXTURE_WALL,
	TEXTURE_EAST,
	TEXTURE_WEST,
	TEXTURE_NORTH,
	TEXTURE_SOUTH,
	TEXTURE_TEST,
	TEXTURE_MAX_COUNT
}	t_texture_type;

typedef enum e_sprite_type
{
	SPRITE_ENEMY,
	SPRITE_MAX_COUNT
}	t_sprite_type;

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

void	draw_sprite_sheet(t_transform tform, size_t index,
			t_sprite_sheet *sprite, t_img_data *img);
bool	glyph_init(char *asset);
void	glyph_end(void);
void	glyph_draw_text(wchar_t *glyphs, t_transform tform,
			t_text_properties prop, t_img_data *img);

#endif