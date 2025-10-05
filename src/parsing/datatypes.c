/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datatypes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 04:44:58 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/05 20:55:09 by vdurand          ###   ########.fr       */
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
	if (!token || !token[0] || ft_strcount(token, '.') > 1
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
	if (!token || !token[0] || (minus_pos != NULL && minus_pos != token)
		|| !ft_strcheck(token + (minus_pos == token), ft_isdigit))
		return (ERROR_ARG_NAN);
	temp = ft_atoi(token);
	if (arg->limited)
	{
		if (temp < arg->int_min || temp > arg->int_max)
			return (ERROR_ARG_LIMITS);
	}
	temp_ptr = malloc(sizeof(int));
	if (!temp_ptr)
		return (ERROR_PARSING_ALLOC);
	*temp_ptr = temp;
	*value = temp_ptr;
	return (ERROR_NONE);
}

t_error	handle_uint(char *token, void **value, t_argument *arg)
{
	t_error	error;

	error = handle_int(token, value, arg);
	if (*value && *(int *)value < 0)
		return (ERROR_ARG_UNSIGNED);
	return (error);
}

t_error	handle_string(char *token, void **value, t_argument *arg)
{
	char			*string;
	size_t			length;

	if (!token)
		return (ERROR_ARG_INVALID);
	if (arg->limited)
	{
		length = ft_strlen(token);
		if (length < arg->array_size)
			return (ERROR_ARG_LIMITS);
	}
	string = ft_strdup(token);
	if (!string)
		return (ERROR_PARSING_ALLOC);
	*value = string;
	return (ERROR_NONE);
}
