/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:22:29 by halnuma           #+#    #+#             */
/*   Updated: 2025/07/24 20:24:56 by vdurand          ###   ########.fr       */
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

# define GAME_NAME	L"CUB3D"
# define GAME_NAME_F	L"»9t~*«CUB3D"

# define WINDOW_WIDTH		1024
# define WINDOW_HEIGHT		768

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
# define TEXT_MAX_SIZE		1000

# define S_BUTTON_INTERACT	100
# define S_BUTTON_OUTL		4
# define INTERACTION_RANGE	2
# define TXTBOX_X_START		350

# define MENU_ACTIONS	2
# define MENU_OPTION_PLAY	L"»5«PLAY"
# define MENU_OPTION_RESUME	L"»5«RESUME"
# define MENU_OPTION_CONFIG	L"»4«Config"
# define MENU_OPTION_QUIT	L"»4«Quit"


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
	t_bbox	bbox;
	t_vec3	position;
	t_vec2	direction;
	float	rad_direction;
	float	accel;
	float	jump_velocity;
	t_vec2	last_move;
	bool	is_grounded;
}	t_player;

typedef struct s_parsing_content
{
	int	player;
	int	pnjs;
	int	enemies;
}	t_parsing_content;

typedef struct s_pnj
{
	t_vec3			position;
	char			**text;
}	t_pnj;

typedef struct s_enemy
{
	t_vec3			position;
	int				hp;
	char			**text;
	t_enemy_state	state;
}	t_enemy;

typedef struct s_menu
{
	int		action;
}	t_menu;

typedef struct s_interaction
{
	int	pnj_id;
	int	count;
}	t_interaction;

typedef struct s_game
{
	void			*mlx;
	char			*win;
	t_img_data		*frame;
	int				map_width;
	int				map_height;
	int				w_width;
	int				w_height;
	int				w_halfwidth;
	int				w_halfheight;
	t_player		player;
	char			**file_content;
	char			**map;
	char			**paths;
	char			**colors;
	char			**pnj_text;
	t_png_pixel8	f_color;
	t_png_pixel8	c_color;
	t_tilemap		*tilemap;
	uint8_t			*z_buffer;
	t_key			key_buffer[KEY_MAX_COUNT];
	t_png			*textures[TEXTURE_MAX_COUNT];
	t_enemy			enemies[MAX_ENEMIES];
	int				enemy_count;
	t_pnj			pnjs[MAX_PNJ];
	int				pnj_count;
	t_interaction	interaction;
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
int			key_released(int key_pressed, void *param);
int			key_pressed(int key_pressed, void *param);
bool		key_check(t_key_type type, t_game *game);
bool		key_is_released(t_key_type type, t_game *game);
bool		key_is_pressed(t_key_type type, t_game *game);

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

// ----- UTILS ----- //
int			check_file_extension(char *filename);
char		**read_map(char *map_file, t_game *game);
void		parsing(t_game *game, char *map_file);
void		free_map(char **map);
bool		is_file_valid(char *path);

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
int			check_player(t_game *game, int i, int j, int *player);
int			check_enemies(t_game *game, int i, int j, int *e);
int			check_pnjs(t_game *game, int i, int j, int *p);



// ----- MINIMAP ----- //
void		draw_minimap(t_game *game);
void		draw_player(t_game *game);
void		draw_tile(t_tile_context *tile, t_png_pixel8 color, int mid_off);
void		draw_pnj(t_tile_context *tile, t_png_pixel8 color);
void		draw_border(t_game *game);
void		draw_player(t_game *game);
void		draw_full_map(t_game *game);


// ----- PNJ ----- //
void		manage_pnjs(t_game *game);
void		draw_interact_button(t_game *game, t_button *btn, int text_box);
void		draw_textbox(t_game *game, char *text, uint64_t time);

int			mouse_move(int x, int y, t_game *game);
void		update_player(t_player *player, t_game *game);
void		player_add_x(float value, t_player *player);
void		player_add_y(float value, t_player *player);
void		player_add_z(float value, t_player *player);

void		draw_enemies(t_game *game);
void		draw_button(t_game *game, t_button *btn);
t_vec2		calculate_axis_dist(t_vec2 p_pos, t_vec2 e_pos);
float		calculate_distance(t_vec2 p_pos, t_vec2 e_pos, t_vec2 axis_dist);
void		render_menu(t_game *game, int start);

#endif