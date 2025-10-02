/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glyphs_effects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 00:08:25 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/02 14:45:51 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glyphs.h"
#include "cub3d.h"

bool	geffect_typewrite(t_text_context *ctx)
{
	size_t	end_index;

	end_index = (get_time_ms() - ctx->start_time) / 50;
	return (ctx->index < end_index);
}

void	geffect_wave(t_text_context *ctx, t_transform *temp)
{
	size_t	anim_index;
	size_t	dif;

	anim_index = ((get_time_ms() - ctx->start_time) / 50) % ctx->length;
	dif = (ctx->index - anim_index - 1) % 10;
	temp->y -= (0.6 * dif);
}

void	geffect_rainbow(t_text_context *ctx, t_transform *temp)
{
	size_t	anim_index;

	anim_index = ((get_time_ms() - ctx->start_time) / 200 - ctx->index) % 26;
	temp->color = g_color_text[anim_index];
}
