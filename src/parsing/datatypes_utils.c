/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datatypes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 17:25:39 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/07 03:01:49 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	dt_check_prefix(char *token, t_argument *arg)
{
	size_t	length;

	if (!token)
		return (false);
	length = ft_strlen(token);
	if (length < 2)
		return (false);
	if (arg->array)
	{
		if (token[0] != '[' || token[length - 1] != ']')
			return (false);
	}
	else if (arg->type == DT_STRUCT
		&& (token[0] != '{' || token[length - 1] != '}'))
		return (false);
	ft_memmove(token, token + 1, length - 2);
	token[length - 2] = '\0';
	return (true);
}

t_vec3	sdt_get_vec3(void *values)
{
	void	**structure;
	t_vec3	result;

	if (!values)
		return ((t_vec3){0, 0, 0});
	structure = ((void **)values);
	result = (t_vec3){*(float *)structure[0], *(float *)structure[1],
		*(float *)structure[2]};
	return (result);
}

t_svec2	sdt_get_tile(void *values)
{
	void	**structure;

	if (!values)
		return ((t_svec2){0, 0});
	structure = ((void **)values);
	return ((t_svec2){*(int *)structure[0], *(int *)structure[1]});
}
