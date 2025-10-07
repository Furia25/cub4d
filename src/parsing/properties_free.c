/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:55:33 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/07 05:50:49 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static inline void	free_property_values(uint8_t mask, void **values,
						size_t size, t_argument *args);

static inline void	free_property_array(void *value)
{
	t_dt_array	*array;

	array = (t_dt_array *)value;
	if (!array)
		return ;
	if (array->length > 0)
		free_property_values(2, array->values, array->length, &array->template);
	free(array->template.name);
	free(array);
}

static inline void	free_property_struct(void *value, t_argument *actual)
{
	const t_data_subtype_info	*subtype;

	subtype = &g_data_subtype_info[actual->subtype];
	free_property_values(true, value, arguments_length(subtype->fields),
		(t_argument *)subtype->fields);
}

static inline void	free_property_values(uint8_t mask, void **values,
						size_t size, t_argument *args)
{
	t_argument			*actual;
	size_t				index;

	index = 0;
	while (index < size)
	{
		if (values && values[index] != NULL)
		{
			if (mask == 2)
				actual = args;
			else
				actual = args + index;
			if (actual->array > 0)
				free_property_array(values[index]);
			else if (actual->type == DT_STRUCT)
				free_property_struct(values[index], actual);
			else
				free(values[index]);
			values[index] = NULL;
		}
		index++;
	}
	if (mask == 1)
		free(values);
}

void	free_tokens(char **tokens, size_t argc)
{
	size_t	index;

	if (!tokens)
		return ;
	index = 0;
	while (index < argc)
	{
		free(tokens[index]);
		index++;
	}
	free(tokens);
}

void	property_inputs_free(t_prop_inputs *inputs)
{
	if (!inputs)
		return ;
	if (!inputs->vla)
		free_tokens(inputs->argv, inputs->argc + 1);
	if (inputs->values)
	{
		free_property_values(!inputs->vla, inputs->values,
			inputs->argc, (t_argument *)inputs->arguments);
	}
	inputs->arguments = NULL;
	inputs->property = NULL;
	inputs->values = NULL;
	inputs->argv = NULL;
}
