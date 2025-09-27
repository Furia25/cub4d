/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parsing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:17:28 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/27 02:51:47 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_PARSING_H
# define CUB3D_PARSING_H

# include "cub3d_structs.h"

# define PARSING_MAP_MESSAGE "INFO : Map size parsed to %dx%d\n"

typedef struct s_game	t_game;

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
	PROP_UNKNOWN
}	t_property_type;

typedef	struct s_property
{
	char	**argv;
	int		argc;
}	t_property;

typedef struct s_parsing
{
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
}	t_parsing;

extern const char *g_property_token[PROP_UNKNOWN];

/*Parsing*/
void	parsing(char *file_name, t_game *game);
int		check_file_extension(char *filename);
void	try_parse_map(int index, t_parsing *parsing, t_game *game);

/*Interpret*/
void	interpret_map_from_file(t_parsing *parsing, t_game *game);

/*Parsing Properties*/
size_t	property_token_length(t_property_type type);

void	parse_property_height(char *line, t_property_type type,
			t_parsing *parsing, t_game *game);
void	parse_property_color(char *line, t_property_type type,
			t_parsing *parsing, t_game *game);
void	parse_property_wall(char *line, t_property_type type,
			t_parsing *parsing, t_game *game);
void	parse_property_entity(char *line, t_property_type type,
			t_parsing *parsing, t_game *game);

/*Tile Symbols*/
bool	is_symbol_player(char c);
bool	is_symbol_border(char c);
bool	is_symbol_central(char c);
bool	is_symbol_valid(char c);

/*Utils*/
bool	is_str_empty(char *str);
void	map_set_player_pos(int x, int y, t_parsing *parsing, t_game *game);

#endif