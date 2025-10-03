/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 20:20:00 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/03 20:34:31 by vdurand          ###   ########.fr       */
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
	if (type == TYPE_ARRAY)
		return (arg->limit_max != 0);
	if (type == TYPE_FLOAT)
		return (arg->limit_min != FLT_MIN || arg->limit_max != FLT_MAX);
	if (type == TYPE_INT)
		return (arg->limit_min != INT_MIN || arg->limit_max != INT_MAX);
	return (false);
}
