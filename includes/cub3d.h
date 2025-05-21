/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:22:29 by halnuma           #+#    #+#             */
/*   Updated: 2025/05/21 11:25:40 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"

# define ESCAPE 65307

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
}	t_game;

int		check_file_extension(char *filename);
void	run_game(t_game *game);
int		exit_game(t_game *game);
int		key_hook(int key_pressed, void *param);
char	**read_map(char *map_file, t_game *game);
void	check_map_errors(t_game *game, char *map_file);
void	free_map(char **map);

#endif