/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:22:29 by halnuma           #+#    #+#             */
/*   Updated: 2025/07/02 13:52:35 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <sys/time.h>
# include <X11/keysymdef.h>
# include <X11/Xlib.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

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
# define MAX_PNJ			10

# define S_BUTTON_INTERACT	100
# define S_BUTTON_OUTL		4
# define INTERACTION_RANGE	2
# define TXTBOX_X_START		350

# define INTERACT_DELAY		150000 

static wchar_t *g_pnj_text_0[] = {
	L"»2T«PNJ 1 : texte 1",
	L"»2T«PNJ 1 : texte 2",
	L"»2T«PNJ 1 : texte 3",
	L"»2T«PNJ 1 : texte 4",
	L"»2T«PNJ 1 : texte 5",
	L"»2T«PNJ 1 : texte 6",
	L"»2T«PNJ 1 : texte 7",
	L"»2T«PNJ 1 : texte 8",
	L"»2T«PNJ 1 : texte 9",
	NULL
};

static wchar_t *g_pnj_text_1[] = {
	L"»2T«PNJ 2 : texte 1",
	L"»2T«PNJ 2 : texte 2",
	L"»2T«PNJ 2 : texte 3",
	L"»2T«PNJ 2 : texte 4",
	L"»2T«PNJ 2 : texte 5",
	L"»2T«PNJ 2 : texte 6",
	L"»2T«PNJ 2 : texte 7",
	L"»2T«PNJ 2 : texte 8",
	L"»2T«PNJ 2 : texte 9",
	NULL
};

static wchar_t *g_pnj_text_2[] = {
	L"»2T«PNJ 3 : texte 1",
	L"»2T«PNJ 3 : texte 2",
	L"»2T«PNJ 3 : texte 3",
	L"»2T«PNJ 3 : texte 4",
	L"»2T«PNJ 3 : texte 5",
	L"»2T«PNJ 3 : texte 6",
	L"»2T«PNJ 3 : texte 7",
	L"»2T«PNJ 3 : texte 8",
	L"»2T«PNJ 3 : texte 9",
	NULL
};

static wchar_t *g_pnj_text_3[] = {
	L"»2T«PNJ 4 : texte 1",
	L"»2T«PNJ 4 : texte 2",
	L"»2T«PNJ 4 : texte 3",
	L"»2T«PNJ 4 : texte 4",
	L"»2T«PNJ 4 : texte 5",
	L"»2T«PNJ 4 : texte 6",
	L"»2T«PNJ 4 : texte 7",
	L"»2T«PNJ 4 : texte 8",
	L"»2T«PNJ 4 : texte 9",
	NULL
};

static wchar_t *g_pnj_text_4[] = {
	L"»2T«PNJ 5 : texte 1",
	L"»2T«PNJ 5 : texte 2",
	L"»2T«PNJ 5 : texte 3",
	L"»2T«PNJ 5 : texte 4",
	L"»2T«PNJ 5 : texte 5",
	L"»2T«PNJ 5 : texte 6",
	L"»2T«PNJ 5 : texte 7",
	L"»2T«PNJ 5 : texte 8",
	L"»2T«PNJ 5 : texte 9",
	NULL
};

static wchar_t *g_pnj_text_5[] = {
	L"»2T«PNJ 6 : texte 1",
	L"»2T«PNJ 6 : texte 2",
	L"»2T«PNJ 6 : texte 3",
	L"»2T«PNJ 6 : texte 4",
	L"»2T«PNJ 6 : texte 5",
	L"»2T«PNJ 6 : texte 6",
	L"»2T«PNJ 6 : texte 7",
	L"»2T«PNJ 6 : texte 8",
	L"»2T«PNJ 6 : texte 9",
	NULL
};

static wchar_t *g_pnj_text_6[] = {
	L"»2T«PNJ 7 : texte 1",
	L"»2T«PNJ 7 : texte 2",
	L"»2T«PNJ 7 : texte 3",
	L"»2T«PNJ 7 : texte 4",
	L"»2T«PNJ 7 : texte 5",
	L"»2T«PNJ 7 : texte 6",
	L"»2T«PNJ 7 : texte 7",
	L"»2T«PNJ 7 : texte 8",
	L"»2T«PNJ 7 : texte 9",
	NULL
};

static wchar_t *g_pnj_text_7[] = {
	L"»2T«PNJ 8 : texte 1",
	L"»2T«PNJ 8 : texte 2",
	L"»2T«PNJ 8 : texte 3",
	L"»2T«PNJ 8 : texte 4",
	L"»2T«PNJ 8 : texte 5",
	L"»2T«PNJ 8 : texte 6",
	L"»2T«PNJ 8 : texte 7",
	L"»2T«PNJ 8 : texte 8",
	L"»2T«PNJ 8 : texte 9",
	NULL
};

static wchar_t *g_pnj_text_8[] = {
	L"»2T«PNJ 9 : texte 1",
	L"»2T«PNJ 9 : texte 2",
	L"»2T«PNJ 9 : texte 3",
	L"»2T«PNJ 9 : texte 4",
	L"»2T«PNJ 9 : texte 5",
	L"»2T«PNJ 9 : texte 6",
	L"»2T«PNJ 9 : texte 7",
	L"»2T«PNJ 9 : texte 8",
	L"»2T«PNJ 9 : texte 9",
	NULL
};

static wchar_t *g_pnj_text_9[] = {
	L"»2T«PNJ 10 : texte 1",
	L"»2T«PNJ 10 : texte 2",
	L"»2T«PNJ 10 : texte 3",
	L"»2T«PNJ 10 : texte 4",
	L"»2T«PNJ 10 : texte 5",
	L"»2T«PNJ 10 : texte 6",
	L"»2T«PNJ 10 : texte 7",
	L"»2T«PNJ 10 : texte 8",
	L"»2T«PNJ 10 : texte 9",
	NULL
};

static wchar_t **g_pnj_text[MAX_PNJ] = {
	g_pnj_text_0,
	g_pnj_text_1,
	g_pnj_text_2,
	g_pnj_text_3,
	g_pnj_text_4,
	g_pnj_text_5,
	g_pnj_text_6,
	g_pnj_text_7,
	g_pnj_text_8,
	g_pnj_text_9
};

typedef enum e_game_state
{
	MENU,
	PLAYING,
	PAUSED
}	t_game_state;

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

typedef struct s_pnj
{
	t_vec2			position;
	wchar_t			**text;
}	t_pnj;

typedef struct s_enemy
{
	t_vec2			position;
	int				hp;
	wchar_t			**text;
	t_enemy_state	state;
}	t_enemy;

typedef struct s_menu
{
	t_png	*assets[ASSET_MAX_COUNT];
	bool	action;
}	t_menu;

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
	t_enemy			pnjs[MAX_PNJ];
	int				pnj_count;
	int				interaction;
	t_game_state	state;
	t_menu			menu;
	t_rng_state		rng;
	uint64_t		start_time;
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
	t_png	*texture;
	int		wall_start;
	int		wall_start_actual;
	int		wall_end;
	int		wall_end_actual;
	int		wall_height;
	int		tex_x;
}	t_texture_context;

typedef struct s_button
{
	t_png_pixel8	color_light;
	t_png_pixel8	color_dark;
	t_png_pixel8	color_out;
	int				width;
	int				height;
	int				x;
	int				y;
	int				shadow_size;
}	t_button;

void		render(t_game *game);
void		run_game(t_game *game);
int			exit_game(t_game *game);
int			game_loop(void *param);
uint64_t	get_time_ms(void);
uint64_t	get_elapsed_ms(void);
uint64_t	time_init(void);

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
void		draw_tile(t_tile_context *tile, t_png_pixel8 color, int mid_off);
void		draw_pnj(t_tile_context *tile, t_png_pixel8 color);
void		draw_border(t_game *game);
void		draw_player(t_game *game);
void		draw_full_map(t_game *game);

int			mouse_move(int x, int y, t_game *game);
void		update_player(t_player *player, t_game *game);
void		draw_enemies(t_game *game);
void		draw_button(t_game *game, t_button *btn);
void		manage_pnjs(t_game *game);
t_vec2		calculate_axis_dist(t_vec2 p_pos, t_vec2 e_pos);
float		calculate_distance(t_vec2 p_pos, t_vec2 e_pos, t_vec2 axis_dist);
void		render_start_menu(t_game *game);
void		render_pause_menu(t_game *game);

#endif