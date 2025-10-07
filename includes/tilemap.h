/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilemap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 21:54:34 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/07 18:00:55 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TILEMAP_H
# define TILEMAP_H
# include <stddef.h>
# include <stdbool.h>
# include "crazypng.h"
# include "cub3d_textures.h"

# define SYMBOL_PLAYER_EAST	'E'
# define SYMBOL_PLAYER_NORTH	'N'
# define SYMBOL_PLAYER_SOUTH	'S'
# define SYMBOL_PLAYER_WEST	'W'
# define SYMBOL_WALL	'1'
# define SYMBOL_GRASS	'0'
# define SYMBOL_WATER	'2'
# define SYMBOL_HELPER	'+'

typedef enum e_tile_solid_mode
{
	SOLID_NONE = 0,
	SOLID_CEIL = 1,
	SOLID_FLOOR = 1 << 1,
	SOLID_WALL = 1 << 2,
	SOLID_ALL = SOLID_CEIL | SOLID_FLOOR | SOLID_WALL
}	t_tile_solid_mode;

typedef enum e_tile_type
{
	TILE_EMPTY,
	TILE_GRASS,
	TILE_WALL,
	TILE_WATER,
	TILE_MAX
}	t_tile_type;

typedef struct t_tile_data
{
	t_tile_type		type;
	t_texture_type	texture;
	t_texture_type	texture_topbot;
	int				solid;
	bool			visible;
	float			ceil_offset;
	float			floor_offset;
	const char		*name;
}	t_tile_data;

typedef struct s_tile
{
	float		ceiling;
	float		floor;
	t_tile_type	type;
	t_tile_data	info;
}	t_tile;

typedef struct s_tilemap
{
	t_tile			**tiles;
	size_t			width;
	size_t			height;
	size_t			tile_size;
}	t_tilemap;

extern const t_tile_data	g_base_tile_info[TILE_MAX];

t_tilemap	*tilemap_new(size_t width, size_t height, size_t tile_size);
void		tilemap_free(t_tilemap *map);
void		tilemap_free_tiles(t_tilemap *map);

bool		tilemap_is_tile_valid(size_t x, size_t y, t_tilemap *map);
t_tile		*tilemap_get_tile(size_t x, size_t y, t_tilemap *map);
bool		tilemap_collision(float x, float y, t_vec2 z, t_tilemap *tilemap);
bool		tilemap_collide_bbox(t_vec3 axis, t_bbox bbox, t_tilemap *map);

t_tilemap	*tilemap_from_tab(char **tab, size_t width,
				size_t height, size_t tile_size);
void		tilemap_tiles_from_str(char *str, size_t line, t_tilemap *map);
t_tile_type	tiletype_from_symbol(char symbol);

#endif