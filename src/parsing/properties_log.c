/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties_log.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:50:22 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/05 04:34:39 by vdurand          ###   ########.fr       */
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

void	print_property_error(int line, t_error error, t_property *property)
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
	print_argument(true, false, argument);
	ft_printf_fd(2, ", got '%s' ", token);
	ft_printf_fd(2, "(%s)\n", g_errors[error]);
}
				
static inline void	print_struct_enum(bool verbose, bool name,
						const t_data_subtype_info *sub);

void	print_argument(bool verbose, bool name, const t_argument *arg)
{
	const t_data_subtype_info	*sub = &g_data_subtype_info[arg->subtype];

	write(1, '<', arg->optional);
	if (name)
		ft_printf("%s: ", arg->name);
	if (sub->name != NULL)
	{
		ft_printf("%s ", sub->name);
		if (verbose)
			print_struct_enum(verbose, name, sub);
	}
	else
		ft_putstr_fd(g_data_type_info[arg->type].name, 1);
	if (arg->array && arg->array_size != 0)
		ft_printf("[%zu]", arg->array_size);
	else if (arg->array)
		ft_putstr_fd("[]", 1);
	if (arg->limited)
	{
		if (arg->type == DT_INT)
			ft_printf("(%d-%d)", arg->int_min, arg->int_max);
		else if (arg->type == DT_FLOAT)
			ft_printf("(%f-%f)", arg->fl_min, arg->fl_max);
	}
	write(1, '<', arg->optional);
}

static inline void	print_struct_enum(bool verbose, bool name,
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
			ft_putstr_fd(", ", 1);
		else if (index > 0)
			ft_putstr_fd(", ", 1);
		if (tab == sub->fields)
			print_argument(verbose, name, (t_argument *)tab + index);
		else
			ft_putstr_fd((char *)tab + index, 1);
		index++;
	}
}
