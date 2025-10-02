/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 09:50:02 by halnuma           #+#    #+#             */
/*   Updated: 2025/10/02 11:41:09 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_border(int i, int j, t_button *btn)
{
	return ((j <= S_BUTTON_OUTL
			&& (i > S_BUTTON_OUTL && i < (btn->width - S_BUTTON_OUTL)))
		|| (j >= btn->height - S_BUTTON_OUTL && (i > S_BUTTON_OUTL
				&& i < (btn->width - S_BUTTON_OUTL)))
		|| (i < S_BUTTON_OUTL && (j > S_BUTTON_OUTL
				&& j < (btn->height - S_BUTTON_OUTL)))
		|| (i > btn->width - S_BUTTON_OUTL && (j > S_BUTTON_OUTL
				&& j < (btn->height - S_BUTTON_OUTL))));
}

static int	is_corner(int i, int j, t_button *btn)
{
	return ((i <= S_BUTTON_OUTL && j <= S_BUTTON_OUTL)
		|| (i <= S_BUTTON_OUTL && j >= btn->height - S_BUTTON_OUTL)
		|| (i >= btn->width - S_BUTTON_OUTL && j <= S_BUTTON_OUTL)
		|| (i >= btn->width - S_BUTTON_OUTL
			&& j >= btn->height - S_BUTTON_OUTL));
}

static int	is_shadow(int i, int j, t_button *btn)
{
	return (i < btn->shadow_size + S_BUTTON_OUTL
		|| (j > btn->height - (btn->shadow_size + S_BUTTON_OUTL)));
}

void	draw_button(t_game *game, t_button *btn)
{
	int				i;
	int				j;

	i = -1;
	while (++i < btn->width)
	{
		j = 0;
		while (j < btn->height)
		{
			if (is_corner(i, j, btn))
			{
				j++;
				continue ;
			}
			if (is_border(i, j, btn))
				draw_pixel(btn->color_out, i + btn->x, j + btn->y, game->frame);
			else if (is_shadow(i, j, btn))
				draw_pixel(btn->color_dark, i + btn->x,
					j + btn->y, game->frame);
			else
				draw_pixel(btn->color_light, i + btn->x,
					j + btn->y, game->frame);
			j++;
		}
	}
}
