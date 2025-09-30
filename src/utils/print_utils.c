/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 17:45:56 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/30 23:23:30 by vdurand          ###   ########.fr       */
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
	ft_putstr_fd(ANSI_CARRIAGE ANSI_ERASE, 1);
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
	ft_putstr_fd(ANSI_SEQUENCE_DOWN, 2);
	print_loading(loaded, loading_max, bar);
	if (error && error_format && str)
	{
		ft_putstr_fd(ANSI_CARRIAGE ANSI_ERASE, 1);
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
