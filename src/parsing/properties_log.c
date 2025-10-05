/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties_log.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:50:22 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/05 18:27:21 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parsing.h"
#include "ft_printf.h"
#include "stdlib.h"
#include "stdbool.h"
#include "stdio.h"

/*
Error: line 16: 'ENTITY': Invalid Values
	x : expected <int[5]>, got 'fsdfsdf'
	name : expected string, got 'fdfdfd' (out of range)
*/

void	print_property_usage(int fd, const t_property *property)
{
	size_t	index;
	size_t	length;

	index = 0;
	if (!property)
		return ;
	length = arguments_length(property->args);
	ft_printf_fd(fd, "Usage : '%s'(", property->name);
	while (index < length)
	{
		print_argument(fd, true, true, &property->args[index]);
		index++;
	}
	if (property->variable)
		ft_putstr_fd("...", fd);
	ft_putstr_fd(")\n", fd);
}

void	print_property_error(int line, t_error error,
			const t_property *property)
{
	ft_printf_fd(2, "Error: line %d: '%s': %s\n",
		line, property->name, g_errors[error]);
}

void	print_error_argument(int depth, t_error error,
			char *token, t_argument *argument)
{
	ft_putchar_fd('\t', 2);
	while (depth > 0)
	{
		ft_putchar_fd('\t', 2);
		depth--;
	}
	ft_printf_fd(2, "- %s : expected ", argument->name);
	print_argument(2, true, false, argument);
	ft_printf_fd(2, ", got '%s' ", token);
	ft_printf_fd(2, "(%s)\n", g_errors[error]);
}
				
static inline void	print_struct_enum(int fd, bool verbose, bool name,
						const t_data_subtype_info *sub);

void	print_argument(int fd, bool verbose, bool name, const t_argument *arg)
{
	const t_data_subtype_info	*sub = &g_data_subtype_info[arg->subtype];

	if (arg->optional)
		ft_putchar_fd('<', fd);
	if (name)
		ft_printf_fd(fd, "%s: ", arg->name);
	if (sub->name != NULL)
	{
		ft_printf_fd(fd, "%s ", sub->name);
		if (verbose)
			print_struct_enum(fd, verbose, name, sub);
	}
	else
		ft_putstr_fd((char *)(g_data_type_info[arg->type].name), fd);
	if (arg->array && arg->array_size != 0)
		ft_printf_fd(fd, "[%zu]", arg->array_size);
	else if (arg->array)
		ft_putstr_fd("[]", fd);
	if (arg->limited)
	{
		if (arg->type == DT_INT)
			ft_printf_fd(fd, "(%d-%d)", arg->int_min, arg->int_max);
		else if (arg->type == DT_FLOAT)
			ft_printf_fd(fd, "(%f-%f)", arg->fl_min, arg->fl_max);
	}
	if (arg->optional)
		ft_putchar_fd('<', fd);
}

static inline void	print_struct_enum(int fd, bool verbose, bool name,
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
	while (index < sub->count)
	{
		if (index > 0 && tab == sub->fields)
			ft_putstr_fd(", ", fd);
		else if (index > 0)
			ft_putstr_fd(", ", fd);
		if (tab == sub->fields)
			print_argument(fd, verbose, name, (t_argument *)tab + index);
		else
			ft_putstr_fd((char *)tab + index, fd);
		index++;
	}
}
