/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datatypes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 04:44:58 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/05 05:01:06 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_parsing.h"

t_error	handle_float(char *token, void **value, t_argument *arg)
{
	float	temp;
	char	*minus_pos;

	minus_pos = ft_strchr(token, '-');
	if (ft_strcount(token, '.') > 1
		|| (minus_pos != NULL && minus_pos != token)
		|| !ft_strcheck(token, is_fdigit))
		return (ERROR_ARG_NAN);
	temp = ft_atof(token);
	if (arg->limited)
	{
		if (temp > arg->fl_max || temp < arg->fl_min)
			return (ERROR_ARG_LIMITS);
	}
	*value = malloc(sizeof(float));
	if (!(*value))
		return (ERROR_PARSING_ALLOC);
	*((float *)*value) = temp;
	return (ERROR_NONE);
}
