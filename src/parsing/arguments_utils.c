/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 20:20:00 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/03 21:25:40 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_datatype_numeral(t_data_type type)
{
	return (type == TYPE_INT || type == TYPE_FLOAT);
}

bool	is_argument_limited(t_argument *arg)
{
	t_data_type	type;

	type = arg->type;
	if (type == TYPE_BOOL || type == TYPE_STRING)
		return (false);
	if (type == arg->array)
		return (arg->limit_max != 0);
	if (type == TYPE_FLOAT)
		return (arg->limit_min != FLT_MIN || arg->limit_max != FLT_MAX);
	if (type == TYPE_INT)
		return (arg->limit_min != INT_MIN || arg->limit_max != INT_MAX);
	return (false);
}

void	print_property_usage(const t_property *prop)
{
	const size_t	length = arguments_length(&prop->args);
	t_argument		*argument;
	size_t			index;
	bool			limited;

	ft_printf("Usage : '%s'(", prop->name);
	index = 0;
	while (index < length)
	{
		argument = &prop->args[index];
		write(1, "[", argument->optional);
		ft_printf("%s: ", argument->name);
		ft_putstr_fd(g_datatype_name[argument->type], 1);
		limited = is_argument_limited(argument);
		if (limited && argument->array)
			printf("[%g]", argument->limit_max);
		else if (limited)
			printf("(%g-%g)", argument->limit_min, argument->limit_max);
		write(1, "]", argument->optional);
		index++;
		if (index != length)
			ft_putchar_fd(',', 1);
	}
	ft_putstr_fd(")\n", 1);
}
