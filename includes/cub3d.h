/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:22:29 by halnuma           #+#    #+#             */
/*   Updated: 2025/10/03 20:31:16 by vdurand          ###   ########.fr       */
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
# include <limits.h>
# include <float.h>

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
# include "cub3d_entities.h"

# define GAME_NAME	"CUB3D"
# define GAME_NAME_F	"{9t~*}CUB3D"

# define GAME_INTERVAL_MIN	32

# define WINDOW_WIDTH		1280
# define WINDOW_HEIGHT		720
# define ASPECT_RES			1080
# define MOUSE_SENS			0.001

# define HEIGHT_LIMIT	100
# define PLAYER_STEP_THRESHOLD	0.08

# define SEED_SYSTEM_RAND_FILE	"/dev/urandom"
# define SEED_FALLBACK_DEFAULT	0xCACA
# define SEED_MESSAGE	"Seed have been initialized to %016lx\n."

# define ANSI_BOLD	"\033[1m"
# define ANSI_YELLOW	"\033[1;33m"
# define ANSI_RED	"\033[31m"
# define ANSI_RESET	"\033[0m"
# define ANSI_ERASE	"\033[2K"
# define ANSI_CARRIAGE	"\r"
# define ANSI_SEQUENCE_UP	"\033[%dA"
# define ANSI_SEQUENCE_DOWN	"\033[%dB"

# define INFO_PREFIX	"\033[36mInfo:\033[0m "
# define DEBUG_PREFIX	"\033[34mDebug:\033[0m "
# define LOADING_COLOR	"\033[34m\033[1m"
# define LOADING_BORDER_LEFT	"["
# define LOADING_BORDER_RIGHT	"]"
# define LOADING_PREFIX	"Loading: "
# define LOADING_COLOR_GOOD	"\033[32m"
# define LOADING_CHAR	"*"
# define LOADING_COMPLETE	"\033[34m\033[1mAll assets ready. \
Starting up...\033[0m"

# define WARNING_TEXTURE_ACCESS	"Cannot access texture file at path: \"%s\""
# define WARNING_TEXTURE_NAME	"Texture file name too long at path: \"%s\""
# define WARNING_SEED	"Failed to set seed \
from random source, using fallback : %016lx\n."

# define MAP_TILE_SIZE		32
# define MMAP_TILE_SIZE		16
# define MINIMAP_SIZE		249
# define MINIMAP_BORDER		5
# define MINIMAP_P_SIZE		8
# define MINIMAP_X_START 	20
# define MINIMAP_Y_START 	20

# define PLAYER_SIZE		0.25

# define TEXT_MAX_SIZE		1000

# define S_BUTTON_INTERACT	100
# define S_BUTTON_OUTL		4
# define INTERACTION_RANGE	0.4

# define MENU_ACTIONS	2
# define MENU_OPTION_PLAY	"{5}PLAY"
# define MENU_OPTION_RESUME	"{5}RESUME"
# define MENU_OPTION_CONFIG	"{4}Config"
# define MENU_OPTION_QUIT	"{4}Quit"
# define DEATH_MESSAGE	"\n\n\
▗▖  ▗▖▄▄▄  █  ▐▌    ▗▄▄▄  ▄ ▗▞▀▚▖   ▐▌\n\
 ▝▚▞▘█   █ ▀▄▄▞▘    ▐▌  █ ▄ ▐▛▀▀▘   ▐▌\n\
  ▐▌ ▀▄▄▄▀          ▐▌  █ █ ▝▚▄▄▖▗▞▀▜▌\n\
  ▐▌                ▐▙▄▄▀ █      ▝▚▄▟▌\n\
\n"

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
	t_sprite	sprite;
	t_animation	anim_start;
	bool		wait_to_flex;
	bool		equipped;
	t_animation	*actual_anim;
	t_animation	anim_idle_off;
	t_animation	anim_idle_on;
	t_animation	anim_flex;
}	t_hud_cigarette;

typedef void	(*t_event_func)(void *ptr, t_game*);

typedef struct s_event
{
	t_event_func	call;
	void			*ptr;
	bool			to_free;
}	t_event;

typedef struct s_game
{
	void				*mlx;
	t_img_data			*frame;
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
	t_vector			*events_postload;
	uint64_t			start_time;
	bool				render_textbox;
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
	float	ent_off_x;
	float	ent_off_y;
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

void		throw_error(t_error error, t_game *game);
void		throw_error_info(t_error error, char *info, t_game *game);
int			exit_game(t_game *game);

void		init_engine_preparsing(t_game *game);
void		init_engine(t_game *game);
int			init_assets(t_game *game);
void		init_textures(t_game *game);
void		init_hooks(t_game *game);
void		start_game(t_game *game);

int			game_loop(void *param);
void		render(t_game *game);

void		color_texture(t_png *tex, t_rgba8 tint);

uint64_t	get_time_ms(void);
uint64_t	get_elapsed_ms(void);
uint64_t	get_fps(uint64_t start_time);
uint64_t	time_init(void);

/* Events queues*/
t_vector	*event_queue_init(t_game *game);
bool		event_queue_push(t_event_func call, void *ptr,
				bool to_free, t_vector *event_queue);
void		event_queue_execute(t_vector *event_queue, t_game *game);

// ----- KEYS ----- //
void		show_keys(t_game *game);
int			key_released(int key_pressed, void *param);
int			key_pressed(int key_pressed, void *param);
bool		key_check(t_key_type type, t_game *game);
bool		key_is_released(t_key_type type, t_game *game);
bool		key_is_pressed(t_key_type type, t_game *game);

// ----- UTILS ----- //
void		free_tab(void **map);
char		**chartab_dup(char **tab, size_t height);
void		free_tab_content(void **map);
bool		is_file_valid(char *path);
int			file_length(char *file);
t_vec3		bbox_get_center(t_bbox bbox);
uint64_t	get_seed(void);
void		rad_to_vect(t_vec2 *direction, float rad);
void		print_char_tab(char **tab);
void		loading_log(int error, char *error_format, char *str);
void		broadcast(char *str, t_game *game);
void		log_game(uint64_t time, t_game *game);

// ----- MINIMAP ----- //
void		draw_minimap(t_game *game);
void		draw_player(t_game *game);
void		draw_tile(t_tile_context *tile, t_rgba8 color,
				int mid_off, int size);
void		draw_border(t_game *game);
void		draw_player(t_game *game);
void		draw_full_map(t_game *game);
int			calculate_offset(double p_pos);
void		map_manage_entities(t_game *game);
void		init_tile_ctx(t_game *game, t_vec3 pos, t_tile_context *tile_info);

void		player_death(t_player *game);
void		update_player(t_player *player, t_game *game);
void		player_add_z(float value, t_player *player);
void		object_move(t_vec3 offset, t_vec3 *pos, t_bbox *bbox);
void		object_set_pos(t_vec3 new_pos, t_vec3 *pos, t_bbox *bbox);

bool		is_pixel_valid(int x, int y, t_img_data *img);
int			is_fdigit(int c);

void		anim_tile_update(t_tile_animation *anim, t_game *game);

void		handle_interactions(t_game *game);
void		check_interaction(t_entity *self, t_game *game);

#endif