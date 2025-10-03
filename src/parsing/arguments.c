/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:44:57 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/03 21:17:13 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parsing.h"

static const char	*g_datatype_name[TYPE_MAX] = {
[TYPE_BOOL] = "BOOL",
[TYPE_INT] = "INT",
[TYPE_FLOAT] = "FLOAT"
};

size_t	arguments_length(t_argument *args)
{
	size_t	length;

	if (!args)
		return (0);
	length = 0;
	while (args[length].type != TYPE_NULL)
		length++;
	return (length);
}

/*void	property_check(t_prop_input *args, t_property *prop)
{
	size_t	argc;

	if (!args || args->argv || prop)
	{
		
	}
		return (ERR);
	argc = 0;
	while (arguments->args[argc])
		argc++;
	*
}*/
