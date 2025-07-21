/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:21:27 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/26 00:27:05 by vdurand          ###   ########.fr       */
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
