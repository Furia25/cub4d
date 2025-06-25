/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:22:29 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/25 00:53:11 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <sys/time.h>
# include <X11/keysymdef.h>
# include <X11/Xlib.h>
# include <stdint.h>
# include <stdlib.h>

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include "stdbool.h"
# include "crazypng.h"
# include "math.h"
# include "maths2.h"
# include "maths2_rng.h"
# include "maths2_geometry.h"

# include "tilemap.h"
# include "cub3d_structs.h"
# include "cub3d_drawing.h"
# include "cub3d_textures.h"
# include "cub3d_colors.h"

# define WINDOW_WIDTH		1920
# define WINDOW_HEIGHT		1080

# define MAP_TILE_SIZE		32
# define MMAP_TILE_SIZE		16
# define MINIMAP_SIZE		249
# define MINIMAP_X_START	40
# define MINIMAP_Y_START	784
# define MINIMAP_BORDER		5
# define MOUSE_SENS			0.001
# define MINIMAP_P_SIZE		8

# define PLAYER_SIZE		0.25

# define MAX_ENEMIES		100

typedef enum e_enemy_state
{
	ON_ALERT,
	SLEEPING,
	DEAD
}	t_enemy_state;

typedef struct s_player
{
	float	base_speed;
	float	eye_height;
	float	jump_force;
	float	fov_deg;
	float	accel_speed;
	float	accel_max;
	float	friction;
	float	air_friction;
	t_bbox	collision_box;
	t_vec2	position;
	t_vec2	direction;
	float	rad_direction;
	float	height;
	float	accel;
	float	jump_velocity;
	t_vec2	last_move;
	bool	is_grounded;
}	t_player;

typedef struct s_enemy
{
	t_vec2			position;
	int				hp;
	t_enemy_state	state;
}	t_enemy;

typedef struct s_game
{
	void			*mlx;
	char			*win;
	t_img_data		*img;
	int				width;
	int				height;
	t_player		player;
	char			**file_content;
	char			**map;
	char			**paths;
	char			**colors;
	t_png_pixel8	f_color;
	t_png_pixel8	c_color;
	t_tilemap		*tilemap;
	t_key			key_buffer[KEY_MAX_COUNT];
	t_png			*textures[TEXTURE_MAX_COUNT];
	t_png			*sprites[SPRITE_MAX_COUNT];
	t_enemy			enemies[MAX_ENEMIES];
	int				enemy_count;
	t_rng_state		rng;
}	t_game;

typedef struct s_tile_context
{
	t_game	*game;
	char	*line;
	int		tile;
	int		pos_x;
	int		pos_y;
	int		off_x;
	int		off_y;
}	t_tile_context;

typedef struct s_texture_context
{
	int	column;
	int	wall_start;
	int	wall_end;
	int	wall_height;
	int	tex_x;
}	t_texture_context;

void		render(t_game *game);
void		run_game(t_game *game);
int			exit_game(t_game *game);
int			game_loop(void *param);
uint64_t	get_time_ms(void);

// ----- KEYS ----- //
void		show_keys(t_game *game);
bool		is_key_pressed(t_key_type type, t_game *game);
int			key_released(int key_pressed, void *param);
int			key_pressed(int key_pressed, void *param);
void		handle_keys(t_game *game);
void		handle_key(t_key key, t_game *game);

// ----- MAP_UTILS ----- //
int			check_file_extension(char *filename);
char		**read_map(char *map_file, t_game *game);
void		parsing(t_game *game, char *map_file);
void		free_map(char **map);

// ----- PARSING ----- //
int			check_colors(t_game *game);
int			check_tiles_and_borders(t_game *game);
int			check_paths(t_game *game);
int			center_tile(char c);

// ----- MINIMAP ----- //
void		draw_minimap(t_game *game);
void		rad_to_vect(t_vec2 *direction, float rad);
int			check_corners(t_game *game, double pos_x, double pos_y);

// ----- MAP_UTILS ----- //
int			check_file_extension(char *filename);
char		**read_map(char *map_file, t_game *game);
void		parsing(t_game *game, char *map_file);
void		free_map(char **map);

// ----- PARSING ----- //
int			check_colors(t_game *game);
int			check_tiles_borders(t_game *game);
int			check_paths(t_game *game);
int			center_tile(char c);
int			borders_around(char **map, int i, int j);
int			check_borders(char *line, int row, int line_nb);
int			check_tile_validity(char c);
int			wrapping_tile(char c);
int			center_tile(char c);
int			player_tile(char c);

// ----- MINIMAP ----- //
void		draw_minimap(t_game *game);
void 		draw_player(t_game *game);
void		draw_tile(t_tile_context *tile, t_png_pixel8 color);
void		draw_border(t_game *game);
void		draw_player(t_game *game);
void		handle_full_map(t_game *game);

int			mouse_move(int x, int y, t_game *game);
void		update_player(t_player *player, t_game *game);
void		draw_enemies(t_game *game);


#endif