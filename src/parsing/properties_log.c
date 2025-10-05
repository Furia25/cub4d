/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties_log.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:50:22 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/06 01:56:52 by vdurand          ###   ########.fr       */
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
	ft_printf_fd(2, ", got '%s' ", token);
	ft_printf_fd(2, "(" ANSI_BRIGHT_BLACK "%s" ANSI_RESET ")\n",
		g_errors[error]);
}
				
static inline void	print_struct_enum(int fd, bool verbose,
						const t_data_subtype_info *sub);

void	print_argument(int fd, bool verbose, bool name, const t_argument *arg)
{
	const t_data_subtype_info	*sub = &g_data_subtype_info[arg->subtype];
	char						*type_name;

	if (arg->optional)
		ft_putchar_fd('<', fd);
	if (name)
		ft_printf_fd(fd, ANSI_BRIGHT_CYAN "%s" ANSI_RESET ": ", arg->name);
	if (sub->name != NULL)
		type_name = (char *)sub->name;
	else
		type_name = (char *)(g_data_type_info[arg->type]);
	ft_printf_fd(fd, ANSI_MAGENTA "%s" ANSI_RESET, type_name);
	if (verbose && sub->name)
		print_struct_enum(fd, verbose, sub);
	if (arg->array_size != 0)
		ft_printf_fd(fd, ANSI_BRIGHT_MAGENTA"[%d]"ANSI_WHITE, arg->array_size);
	else if (arg->array)
		ft_putstr_fd(ANSI_BRIGHT_MAGENTA"[]"ANSI_RESET, fd);
	if (arg->limited && arg->type == DT_FLOAT)
		ft_printf_fd(fd, "(%f-%f)", arg->fl_min, arg->fl_max);
	else if (arg->limited )
		ft_printf_fd(fd, "(%d-%d)", arg->int_min, arg->int_max);
	if (arg->optional)
		ft_putstr_fd(ANSI_RESET ">", fd);
	ft_putstr_fd(ANSI_RESET, fd);
}

static inline void	print_struct_enum(int fd, bool verbose,
						const t_data_subtype_info *sub)
{
	size_t		index;
	const void	*tab;

	if (sub->fields)
		tab = sub->fields;
	else if (sub->enum_values)
		tab = sub->enum_values;
	else
		return ;
	index = 0;
	ft_putchar_fd('{', fd);
	while (index < sub->count)
	{
		if (index > 0 && tab == sub->fields)
			ft_putstr_fd(", ", fd);
		else if (index > 0)
			ft_putstr_fd("|", fd);
		if (tab == sub->fields)
			print_argument(fd, verbose, true, (t_argument *)tab + index);
		else
			ft_putstr_fd(((char **)tab)[index], fd);
		index++;
	}
	ft_putchar_fd('}', fd);
}
