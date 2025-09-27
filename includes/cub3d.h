/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:22:29 by halnuma           #+#    #+#             */
/*   Updated: 2025/09/27 16:30:16 by vdurand          ###   ########.fr       */
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
# include "maths2_utils.h"
# include "maths2_easing.h"
# include "vector.h"

# include "tilemap.h"
# include "cub3d_structs.h"
# include "cub3d_drawing.h"
# include "cub3d_textures.h"
# include "cub3d_colors.h"
# include "cub3d_errors.h"
# include "cub3d_anim.h"
# include "cub3d_parsing.h"

//TEMP
# define vec3_print(vec)	printf("x: %f, y: %f, z: %f\n", vec.x, vec.y, vec.z);
# define vec2_print(vec)	printf("x: %f, y: %f\n", vec.x, vec.y);
//TEMP

# define GAME_NAME	"CUB3D"
# define GAME_NAME_F	L"{9t~*}CUB3D"

# define GAME_INTERVAL_MIN	32

# define WINDOW_WIDTH		1280
# define WINDOW_HEIGHT		720
# define ASPECT_RES			1080
# define MOUSE_SENS			0.001

# define MAP_TILE_SIZE		32
# define MMAP_TILE_SIZE		16
# define MINIMAP_SIZE		249
# define MINIMAP_BORDER		5
# define MINIMAP_P_SIZE		8

# define PLAYER_SIZE		0.25

# define TEXT_MAX_SIZE		1000

# define S_BUTTON_INTERACT	100
# define S_BUTTON_OUTL		4
# define INTERACTION_RANGE	2

# define SEED_SYSTEM_RAND_FILE	"/dev/urandom"
# define SEED_FALLBACK_DEFAULT	0xCACA
# define SEED_MESSAGE	"INFO : Seed have been initialized to %016lx\n"

# define WARNING_TEXTURE	"WARNING : Texture at path \
\"%s\" can't be opened\n"
# define WARNING_SEED "WARNING: Failed to set seed \
from random source, using fallback : %016lx\n"

# define MENU_ACTIONS	2
# define MENU_OPTION_PLAY	L"{5}PLAY"
# define MENU_OPTION_RESUME	L"{5}RESUME"
# define MENU_OPTION_CONFIG	L"{4}Config"
# define MENU_OPTION_QUIT	L"{4}Quit"

typedef enum e_game_state
{
	STATE_MENU,
	STATE_PLAYING,
	STATE_PAUSED
}	t_game_state;

typedef struct s_parsing_content
{
	int	player;
	int	npcs;
	int	enemies;
}	t_parsing_content;

typedef struct s_menu
{
	int		action;
}	t_menu;

typedef struct s_interaction
{
	int	npc_id;
	int	count;
}	t_interaction;

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
	float	yaw_rad;
	int		pitch_offset;
	float	accel;
	float	jump_velocity;
	t_vec2	last_move;
	bool	is_grounded;
}	t_player;

typedef struct s_entity_manager
{
	t_vector	*entities;
}	t_entity_manager;

typedef struct s_win
{
	void	*ptr;
	int		width;
	int		height;
	int		halfwidth;
	int		halfheight;
}	t_win;

typedef struct s_hud_cigarette
{
	t_sprite			sprite;
	t_index_animation	anim_start;
	bool				wait_to_flex;
	bool				equipped;
	t_index_animation	*actual_anim;
	t_index_animation	anim_idle_off;
	t_index_animation	anim_idle_on;
	t_index_animation	anim_flex;
}	t_hud_cigarette;

typedef struct s_game
{
	void				*mlx;
	t_img_data			*frame;
	uint8_t				*sky_buffer;
	t_parsing			parsing;
	t_win				win;
	float				aspect_res;
	t_player			player;
	t_tilemap			*tilemap;
	float				*z_buffer;
	t_key				key_buffer[KEY_MAX_COUNT];
	t_png				*textures[TEXTURE_MAX_COUNT];
	t_tile_animation	water_anim;
	t_hud_cigarette		hud_cigarette;
	t_game_state		state;
	t_menu				menu;
	t_rng_state			rng;
	t_entity_manager	entity_manager;
	uint64_t			start_time;
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
	t_rgba8			color_light;
	t_rgba8			color_dark;
	t_rgba8			color_out;
	int				width;
	int				height;
	int				x;
	int				y;
	int				shadow_size;
}	t_button;

void		throw_error(t_game *game, t_error error);
void		throw_error_info(t_game *game, t_error error, char *info);

void		render(t_game *game);

int			exit_game(t_game *game);
int			game_loop(void *param);
void		init_engine(t_game *game);
int			init_assets(t_game *game);
int			init_textures(t_game *game);
void		init_water(t_tile_animation *water_anim, t_game *game);
void		init_hooks(t_game *game);
void		init_game(t_game *game);

void		color_texture(t_png *tex, t_rgba8 tint);

uint64_t	get_time_ms(void);
uint64_t	get_elapsed_ms(void);
uint64_t	get_fps(uint64_t start_time);
uint64_t	time_init(void);

// ----- KEYS ----- //
void		show_keys(t_game *game);
int			key_released(int key_pressed, void *param);
int			key_pressed(int key_pressed, void *param);
bool		key_check(t_key_type type, t_game *game);
bool		key_is_released(t_key_type type, t_game *game);
bool		key_is_pressed(t_key_type type, t_game *game);

// ----- UTILS ----- //
void		free_chartab(char **map);
bool		is_file_valid(char *path);
int			file_length(char *file);
t_vec3		bbox_get_center(t_bbox bbox);
uint64_t	get_seed(void);
void		rad_to_vect(t_vec2 *direction, float rad);

// ----- MINIMAP ----- //
void		draw_minimap(t_game *game, t_ivec2 map_pos);
void		draw_player(t_game *game, t_ivec2 map_pos);
void		draw_tile(t_tile_context *tile, t_rgba8 color,
				int mid_off, t_ivec2 map_pos);
void		draw_border(t_game *game, t_ivec2 map_pos);
void		draw_player(t_game *game, t_ivec2 map_pos);
void		draw_full_map(t_game *game);
int			calculate_offset(double p_pos);
void		map_manage_entities(t_game *game, t_ivec2 map_pos);

// ----- NPC ----- //
void		draw_interact_button(t_game *game, t_button *btn, int text_box);
void		draw_textbox(t_game *game, char *text, uint64_t time, t_ivec2 pos);
//

void		update_player(t_player *player, t_game *game);
void		player_add_x(float value, t_player *player);
void		player_add_y(float value, t_player *player);
void		player_add_z(float value, t_player *player);

void		draw_button(t_game *game, t_button *btn);
void		render_menu(t_game *game, int start);

bool		is_pixel_valid(int x, int y, t_img_data *img);

#endif