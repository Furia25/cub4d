/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilemap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 21:54:34 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/05 23:21:38 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TILEMAP_H
# define TILEMAP_H

/*THIS IS JUST A TEST*/

typedef enum e_texture_type
{
	TEXTURE_NAN,
	TEXTURE_WALL,
	TEXTURE_TEST,
	TEXTURE_MAX_COUNT
}	t_texture_type;

typedef enum e_tile_type
{
	TILE_EMPTY,
	TILE_WALL,
	TILE_MAX_COUNT
}	t_tile_type;

typedef struct t_tile_info
{
	t_tile_type		type;
	bool			solid;
	bool			wall;
	bool			visible;
	t_texture_type	texture;
	const char		*name;
}	t_tile_info;

typedef struct s_tile
{
	t_tile_type	type;
	t_tile_info	info;
}	t_tile;

typedef struct s_tilemap
{
	t_tile	**tiles;
	int		width;
	int		height;
	float	tile_size;
}	t_tilemap;

static const t_tile_info	g_base_tile_info[TILE_MAX_COUNT] = {
[TILE_EMPTY] = {TILE_EMPTY, false, false, false, TEXTURE_NAN, "Empty"},
[TILE_WALL] = {TILE_WALL, true, true, true, TEXTURE_WALL, "Wall"},
};

#endif