/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 15:42:13 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/05 21:04:01 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_fdigit(int c)
{
	if (ft_isdigit(c) || c == '.' || c == '-')
		return (1);
	return (0);
}

t_prop_inputs	property_get_vla(t_prop_inputs *inputs)
{
	t_prop_inputs	result;
	size_t			length;

	result = *inputs;
	length = arguments_length(inputs->arguments);
	result.argc -= length;
	result.argv += length;
	result.values += length;
	return (result);
}
