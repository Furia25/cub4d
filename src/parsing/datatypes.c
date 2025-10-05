/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datatypes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 04:44:58 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/05 17:43:34 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_parsing.h"

t_error	handle_float(char *token, void **value, t_argument *arg)
{
	float	*temp_ptr;
	float	temp;
	char	*minus_pos;

	minus_pos = ft_strchr(token, '-');
	if (!token || ft_strcount(token, '.') > 1
		|| (minus_pos != NULL && minus_pos != token)
		|| !ft_strcheck(token, is_fdigit))
		return (ERROR_ARG_NAN);
	temp = ft_atof(token);
	if (arg->limited)
	{
		if (temp > arg->fl_max || temp < arg->fl_min)
			return (ERROR_ARG_LIMITS);
	}
	temp_ptr = malloc(sizeof(int));
	if (!temp_ptr)
		return (ERROR_PARSING_ALLOC);
	*temp_ptr = temp;
	*value = temp_ptr;
	return (ERROR_NONE);
}

t_error	handle_int(char *token, void **value, t_argument *arg)
{
	int		*temp_ptr;
	int		temp;
	char	*minus_pos;

	minus_pos = ft_strchr(token, '-');
	if (!token || (minus_pos != NULL && minus_pos != token)
		|| !ft_strcheck(token + (minus_pos == token), ft_isdigit))
		return (ERROR_ARG_NAN);
	temp = ft_atoi(token);
	if (arg->limited)
	{
		if (temp > arg->int_max || temp < arg->int_min)
			return (ERROR_ARG_LIMITS);
	}
	temp_ptr = malloc(sizeof(int));
	if (!temp_ptr)
		return (ERROR_PARSING_ALLOC);
	*temp_ptr = temp;
	*value = temp_ptr;
	return (ERROR_NONE);
}

t_error	handle_string(char *token, void **value, t_argument *arg)
{
	char			*string;

	if (!token)
		return (ERROR_ARG_INVALID);
	if (!dt_check_prefix(token, arg))
		return (ERROR_ARG_MALFORMED_STRING);
	string = ft_strdup(token);
	if (!string)
		return (ERROR_PARSING_ALLOC);
	*value = string;
	return (ERROR_NONE);
}
