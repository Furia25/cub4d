/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 17:45:56 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/28 20:17:27 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_printf.h"

void	print_char_tab(char **tab)
{
	while (tab && *tab)
	{
		printf(*(tab + 1) ? "|%s|, " : "|%s|\n", *tab);
		tab++;
	}
}

static inline void	print_loading(int loaded, int max, int *bar)
{
	int	index;
	int	percent;

	index = 0;
	percent = (int)((float)(loaded + 1) / max * 100);
	ft_putstr_fd(LOADING_COLOR LOADING_PREFIX " " LOADING_BORDER_LEFT, 1);
	while (index < max)
	{
		if (index <= loaded)
		{
			if (bar[index] == 1)
				ft_putstr_fd(ANSI_YELLOW LOADING_CHAR, 1);
			else if (bar[index] == 2)
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
	static int	bar[TEXTURE_MAX_COUNT + 4] = {0};
	static int	loaded = -1;
	static int	errors_message = 0;

	if (loaded >= loading_max)
		return ;
	bar[loaded] = error;
	ft_printf(ANSI_SEQUENCE_UP, errors_message + 1);
	print_loading(loaded, loading_max, bar);
	ft_printf(ANSI_SEQUENCE_DOWN, errors_message + 1);
	ft_putstr_fd("\033[2K\r", 1);
	if (error && error_format && str)
	{
		errors_message++;
		if (error == 1)
			ft_putstr_fd(WARNING_PREFIX, 2);
		else
			ft_putstr_fd(ERROR_PREFIX, 2);
		ft_printf(error_format, str);
	}
	ft_putstr_fd("\033[0m", 1);
	ft_printf(ANSI_SEQUENCE_DOWN, 1);
	loaded++;
}
