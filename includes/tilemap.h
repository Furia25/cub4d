/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilemap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 21:54:34 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/20 15:29:25 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TILEMAP_H
# define TILEMAP_H
# include <stddef.h>
# include <stdbool.h>
# include "crazypng.h"
# include "cub3d_textures.h"

typedef enum e_tile_type
{
	TILE_EMPTY,
	TILE_WALL,
	TILE_MAX_COUNT
}	t_tile_type;

typedef struct t_tile_data
{
	t_tile_type		type;
	bool			solid;
	bool			wall;
	bool			visible;
	bool			blocking;
	t_texture_type	texture;
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

/*[TYPE]      = Type, Solid, Wall, Visible, Blocking*/
static const t_tile_data	g_base_tile_info[TILE_MAX_COUNT] = {
[TILE_EMPTY] = {TILE_EMPTY, true, false, false, false, TEXTURE_NAN, "Empty"},
[TILE_WALL] = {TILE_WALL, true, true, true, true, TEXTURE_WALL, "Wall"},
};

t_tilemap	*tilemap_new(size_t width, size_t height, size_t tile_size);
void		tilemap_free(t_tilemap *map);
void		tilemap_free_tiles(t_tilemap *map);

bool		tilemap_is_tile_valid(size_t x, size_t y, t_tilemap *map);
t_tile		*tilemap_get_tile(size_t x, size_t y, t_tilemap *map);
bool		tilemap_collision(float x, float y, float z, t_tilemap *tilemap);
bool		tilemap_collision_bbox(t_vec3 axis, t_bbox bbox, t_tilemap *map);

t_tilemap	*tilemap_from_tab(char **tab, size_t width,
				size_t height, size_t tile_size);
void		tilemap_tiles_from_str(char *str, size_t line, t_tilemap *map);
t_tile_type	tiletype_from_symbol(char symbol);

#endif