/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:21:27 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/23 19:57:30 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint64_t	g_start = 0;

uint64_t	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((uint64_t)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

uint64_t	time_init(void)
{
	uint64_t	time;

	time = get_time_ms();
	g_start = time;
	return (time);
}

uint64_t	get_elapsed_ms(void)
{
	return (get_time_ms() - g_start);
}

uint64_t	get_fps(uint64_t start_time)
{
	static int		fps_time = 0;
	static uint64_t	fps_total = 0;
	static uint64_t	last = 0;
	uint64_t		actual;
	uint64_t		delta;

	if (fps_time == 30)
	{
		fps_total = 0;
		fps_time = 0;
	}
	delta = get_time_ms() - start_time;
	if (delta == 0)
		delta = 1;
	actual = 1000 / delta;
	if (actual < last)
	{
		fps_total = actual;
		fps_time = 1;
	}
	fps_total += actual;
	fps_time += 1;
	return (fps_total / fps_time);
}
