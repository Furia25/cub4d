/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 17:45:56 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/07 04:48:46 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_printf.h"

void	print_char_tab(char **tab)
{
	while (tab && *tab)
	{
		if (*(tab + 1))
			printf("|%s|, ", *tab);
		else
			printf("|%s|\n", *tab);
		tab++;
	}
}

static inline void	print_loading(int loaded, int max, int *bar)
{
	int	index;
	int	percent;

	index = 0;
	percent = (int)((float)(loaded + 1) / max * 100);
	ft_putstr_fd(ANSI_CARRIAGE ANSI_CLEAR_LINE, 1);
	ft_putstr_fd(LOADING_COLOR LOADING_PREFIX " " LOADING_BORDER_LEFT, 1);
	while (index < max)
	{
		if (index <= loaded)
		{
			if (bar[index] == 1)
				ft_putstr_fd(ANSI_YELLOW LOADING_CHAR, 1);
			else if (bar[index] > 1)
				ft_putstr_fd(ANSI_RED LOADING_CHAR, 1);
			else
				ft_putstr_fd(LOADING_COLOR_GOOD LOADING_CHAR, 1);
		}
		else
			ft_putchar_fd(' ', 1);
		index++;
	}
	ft_putstr_fd(LOADING_COLOR LOADING_BORDER_RIGHT " ", 1);
	ft_putnbr_fd(percent, 1);
	ft_putstr_fd("%    " ANSI_RESET, 1);
}

void	loading_log(int error, char *error_format, char *str)
{
	const int	loading_max = TEXTURE_MAX_COUNT + 2;
	static int	bar[TEXTURE_MAX_COUNT + 2] = {0};
	static int	loaded = -1;
	static int	error_occured = 0;

	if (loaded >= 0)
		bar[loaded] = error;
	ft_putstr_fd(ANSI_CURSOR_DOWN, 2);
	print_loading(loaded, loading_max, bar);
	if (error && error_format && str)
	{
		ft_putstr_fd(ANSI_CARRIAGE ANSI_CLEAR_LINE, 1);
		error_occured++;
		if (error == 1)
			ft_putstr_fd(WARNING_PREFIX, 2);
		else
			ft_putstr_fd(ERROR_PREFIX, 2);
		ft_printf_fd(2, error_format, str);
		ft_putstr_fd("\n", 2);
	}
	ft_putstr_fd(ANSI_RESET, 1);
	loaded++;
}

void	log_game(uint64_t time, t_game *game)
{
	static uint16_t	altern = 0;
	uint64_t		time_passed;
	uint32_t		milliseconds;
	uint32_t		seconds;
	uint32_t		minutes;

	if (altern++ % 8 == 0)
		return ;
	time_passed = get_elapsed_ms();
	minutes = time_passed / 60000;
	seconds = (time_passed % 60000) / 1000;
	milliseconds = time_passed % 1000;
	ft_printf(ANSI_CARRIAGE ANSI_CLEAR_LINE "FPS : %d DEATH : %d TIME : ",
		get_fps(time), game->player.deaths);
	if (minutes < 10)
		ft_putchar_fd('0', 1);
	ft_printf("%d:", minutes);
	if (seconds < 10)
		ft_putchar_fd('0', 1);
	ft_printf("%d:", seconds);
	if (milliseconds < 10)
		ft_putstr_fd("00", 1);
	else if (milliseconds < 100)
		ft_putchar_fd('0', 1);
	ft_printf("%d" ANSI_RESET, milliseconds);
}

/*We have to void game here because of event template function*/

void	broadcast(char *str, t_game *game)
{
	(void)game;
	ft_putstr_fd(str, 1);
	ft_putchar_fd('\n', 1);
}
