/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parsing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:17:28 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/03 21:25:06 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_PARSING_H
# define CUB3D_PARSING_H

# include "cub3d_structs.h"
# include "cub3d_errors.h"

# define DEBUG_PARSING	0
# define PARSING_MAP_MESSAGE "Map size parsed to %dx%d.\n"

# define TRUE_STR	"true"
# define FALSE_STR	"false"

# define PROPERTY_AMBIANT_MAX	250

typedef struct s_game	t_game;

typedef enum s_data_type
{
	TYPE_NULL,
	TYPE_INT,
	TYPE_FLOAT,
	TYPE_BOOL,
	TYPE_STRING,
	TYPE_MAX
}	t_data_type;

extern const char	*g_datatype_name[TYPE_MAX];

typedef struct s_argument
{
	const char		*name;
	bool			array;
	t_data_type		type;
	long			limit_min;
	long			limit_max;
	bool			optional;
}	t_argument;

typedef struct s_property
{
	const char	*name;
	bool		variable;
	t_argument	*args;
}	t_property;

typedef enum e_property_type
{
	PROP_NO,
	PROP_SO,
	PROP_WE,
	PROP_EA,
	PROP_F,
	PROP_C,
	PROP_A,
	PROP_ENTITY,
	PROP_HEIGHT,
	PROP_HEIGHT_PRECISE,
	PROP_BROADCAST,
	PROP_COMMENT,
	PROP_UNKNOWN
}	t_property_type;

typedef struct s_prop_input
{
	char	**argv;
	int		argc;
	void	**values;
}	t_prop_input;

typedef struct s_parsing
{
	int				line_num;
	int				file_fd;
	int				file_length;
	char			**file_content;
	char			**map;
	char			*textures_paths[5];
	int				map_width;
	int				map_height;
	int				map_start;
	int				map_end;
	bool			has_player;
	t_rgba8			ambiant_color;
	uint16_t		ambiant_strength;
	t_rgba8			floor_color;
	t_rgba8			ceil_color;
	bool			has_ceil;
	bool			has_floor;
	t_prop_input	temp_prop;
}	t_parsing;

typedef struct s_height_data
{
	int		x;
	int		y;
	int		width;
	int		height;
	float	floor_offset;
	float	ceil_offset;
	bool	precise;
}	t_height_data;

extern const char		*g_property_token[PROP_UNKNOWN];

/*Parsing*/
void		parsing(char *file_name, t_game *game);
int			check_file_extension(char *filename);
void		try_parse_map(int index, t_parsing *parsing, t_game *game);
void		map_check_borders(t_parsing *parsing, t_game *game);

/*Interpret*/
void		interpret_map_from_file(t_parsing *parsing, t_game *game);
void		build_entities(t_parsing *parsing, t_game *game);

/*Properties Arguments*/
size_t	arguments_length(t_argument *args);
bool	is_datatype_numeral(t_data_type type);
bool	is_argument_limited(t_argument *arg);
void	print_property_usage(const t_property *prop);

/*Parsing Properties*/
t_prop_input	property_get_args(char *line, t_property_type type, t_game *game);
bool		property_check_color(t_prop_input prop);
void		apply_height_postload(t_height_data *args, t_game *game);

void		parse_property_broadcast(char *line, t_game *game);
void		parse_property_height(char *line, t_property_type type,
				t_parsing *parsing, t_game *game);
void		parse_property_color(char *line, t_property_type type,
				t_parsing *parsing, t_game *game);
void		parse_property_wall(char *line, t_property_type type,
				t_parsing *parsing, t_game *game);
void		parse_property_entity(char *line, t_property_type type,
				t_parsing *parsing, t_game *game);

/*Tile Symbols*/
bool		is_symbol_player(char c);
bool		is_symbol_border(char c);
bool		is_symbol_central(char c);
bool		is_symbol_valid(char c);

/*Utils*/
void		property_free(void *ptr);
bool		str_remove_chars(char *str, char *set);
bool		is_str_empty(char *str);
void		map_set_player_pos(int x, int y, t_parsing *parsing, t_game *game);

#endif