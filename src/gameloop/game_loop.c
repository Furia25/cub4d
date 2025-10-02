/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:10:04 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/02 16:33:18 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"
#include "cub3d_entities.h"
#include "glyphs.h"
#include "ft_printf.h"

static inline void	hud_cigarette_animator(t_hud_cigarette *hud_cigarette,
						t_game *game);

static inline void	play_loop(t_game *game, uint64_t time)
{
	t_entity_manager	*entities;
	uint64_t			fps;

	entities = &game->entity_manager;
	if (key_is_pressed(KEY_PAUSE, game))
		game->state = STATE_PAUSED;
	entities_tick(entities, game);
	if (entities->can_interact && !entities->interacted
		&& key_is_pressed(KEY_INTERACT, game))
	{
		entities->interacted = entities->can_interact;
		if (entities->interacted->interaction)
			entities->interacted->interaction(entities->interacted, game);
	}
	anim_tile_update(&game->water_anim, game);
	update_player(&game->player, game);
	hud_cigarette_animator(&game->hud_cigarette, game);
	render(game);
	fps = get_fps(time);
	if (fps != 0)
		ft_printf(ANSI_CARRIAGE ANSI_ERASE "FPS : %d" ANSI_RESET, fps);
}

int	game_loop(void *param)
{
	static uint64_t	last_time = 0;
	uint64_t		time;
	t_game			*game;
	t_img_data		*frame;

	game = param;
	frame = game->frame;
	time = get_time_ms();
	if (time >= last_time)
	{
		last_time = time + GAME_INTERVAL_MIN;
		if (key_check(KEY_QUIT, game))
			exit_game(game);
		if (game->state != STATE_MENU && game->state != STATE_PAUSED)
			play_loop(game, time);
		else
			render(game);
		mlx_put_image_to_window(game->mlx, game->win.ptr,
			frame->img_ptr, -2, -2);
	}
	return (1);
}

static inline void	hud_cigarette_animator(t_hud_cigarette *cig,
						t_game *game)
{
	anim_update(cig->actual_anim);
	cig->sprite.transform.index = cig->actual_anim->actual_index;
	if (anim_is_ended(&cig->anim_start)
		&& cig->actual_anim == &cig->anim_start)
		cig->actual_anim = &cig->anim_idle_off;
	if (anim_is_ended(&cig->anim_flex))
	{
		if (cig->equipped)
			cig->actual_anim = &cig->anim_idle_on;
		else
			cig->actual_anim = &cig->anim_idle_off;
	}
	if (key_is_released(KEY_FLEX, game)
		&& (anim_is_ended(cig->actual_anim)
			|| cig->actual_anim == &cig->anim_idle_off
			|| cig->actual_anim == &cig->anim_idle_on))
	{
		cig->wait_to_flex = false;
		cig->equipped = !cig->equipped;
		cig->actual_anim = &cig->anim_flex;
		cig->actual_anim->anim_dir = 1 - (2.5 * !cig->equipped);
		anim_reset(cig->actual_anim);
	}
}

void	start_game(t_game *game)
{
	game->start_time = time_init();
	game->hud_cigarette.actual_anim = &game->hud_cigarette.anim_start;
}
