/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:55:33 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/06 19:49:19 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static inline void	free_property_values(bool is_array, void **values,
						size_t size, const t_argument *args);

static inline void	free_property_array(void *value)
{
	t_dt_array	*array;

	array = (t_dt_array *)value;
	
	if (!array)
		return ;
	free(array->template.name);
	free_property_values(true, array->values, array->length, &array->template);
	free(array);
}

static inline void	free_property_struct(void *value, t_argument *actual)
{
	const t_data_subtype_info	*subtype;

	subtype = &g_data_subtype_info[actual->subtype];
	free_property_values(false, value, arguments_length(subtype->fields),
		subtype->fields);
}

static inline void	free_property_values(bool is_array, void **values,
						size_t size, const t_argument *args)
{
	t_argument	*actual;
	size_t		index;

	index = 0;
	while (index < size)
	{
		if (values[index] != NULL)
		{
			if (is_array)
				actual = (t_argument *)args;
			else
				actual = (t_argument *)(&args[index]);
			if (actual->array > 0)
				free_property_array(values[index]);
			else if (actual->type == DT_STRUCT)
				free_property_struct(values[index], actual);
			else
				free(values[index]);
		}
		index++;
	}
	if (!is_array)
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
		free_property_values(false, inputs->values,
			arguments_length(inputs->arguments), inputs->arguments);
	inputs->arguments = NULL;
	inputs->property = NULL;
	inputs->values = NULL;
	inputs->argv = NULL;
}
