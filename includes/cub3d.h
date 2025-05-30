/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:22:29 by halnuma           #+#    #+#             */
/*   Updated: 2025/05/29 00:32:13 by val              ###   ########.fr       */
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

# define KEY_MEMORY	10

# define WINDOW_WIDTH	1920
# define WINDOW_HEIGHT	1080

typedef enum e_keymap
{
	KEY_QUIT = XK_Escape,
	KEY_TEST = XK_e
}	t_keymap;

typedef struct s_key
{
	uint64_t	time;
	int			keycode;
}	t_key;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_game
{
	void		*mlx;
	char		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			width;
	int			height;
	int			endian;
	int			pos_x;
	int			pos_y;
	int			end;
	char		**map;
	int			steps;
	int			direction;
	t_key		keys[KEY_MEMORY];
}	t_game;

int			check_file_extension(char *filename);
void		run_game(t_game *game);
int			exit_game(t_game *game);
int			key_hook(int key_pressed, void *param);
char		**read_map(char *map_file, t_game *game);
void		check_map_errors(t_game *game, char *map_file);
void		free_map(char **map);
uint64_t	get_time_ms(void);

int			key_released(int key_pressed, void *param);
int			key_pressed(int key_pressed, void *param);
void		handle_keys(t_game *game);
void		handle_key(t_key key, t_game *game);
#endif