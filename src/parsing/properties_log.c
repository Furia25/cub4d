/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties_log.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:50:22 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/06 04:10:58 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parsing.h"
#include "ft_printf.h"
#include "stdlib.h"
#include "stdbool.h"
#include "stdio.h"

void	print_property_usage(int fd, const t_property *property)
{
	size_t	index;
	size_t	length;

	index = 0;
	if (!property)
		return ;
	length = arguments_length(property->args);
	ft_putstr_fd(ANSI_BRIGHT_GREEN "Usage" ANSI_RESET, fd);
	ft_printf_fd(fd, ": " ANSI_BOLD "'%s'" ANSI_RESET "(", property->name);
	while (index < length)
	{
		print_argument(fd, true, true, &property->args[index]);
		index++;
		if (index < length)
			ft_putstr_fd(", ", fd);
	}
	if (property->variable)
		ft_putstr_fd("...", fd);
	ft_putstr_fd(")\n", fd);
}

void	print_property_error(int line, t_error error,
			const t_property *property)
{
	ft_printf_fd(2, ERROR_PREFIX "line %d: '%s': %s\n",
		line, property->name, g_errors[error]);
}

void	print_error_argument(int depth, t_error error,
			char *token, t_argument *argument)
{
	while (depth > 0)
	{
		ft_putstr_fd("  ", 2);
		depth--;
	}
	ft_printf_fd(2, "- " ANSI_BRIGHT_CYAN "%s" ANSI_RESET ": expected ",
		argument->name);
	print_argument(2, false, false, argument);
	ft_putstr_fd(", got ", 2);
	if (argument->array > 0 && token[0] == '[')
		ft_printf_fd(2, "'[%s]' ", token);
	else if (argument->type == DT_STRUCT && token[0] == '{')
		ft_printf_fd(2, "'{%s}' ", token);
	else
		ft_printf_fd(2, "'%s' ", token);
	ft_printf_fd(2, "(" ANSI_BRIGHT_BLACK "%s" ANSI_RESET ")\n",
		g_errors[error]);
}
