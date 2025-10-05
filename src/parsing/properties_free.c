/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:55:33 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/05 18:32:08 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static inline void	free_property_values(void **values, const t_argument *args);

static inline void	free_property_array(void **values, const t_argument *array)
{
	t_argument	template;

	template = *array;
	template.array = false;
	free_property_values(values, &template);
}

static inline void	free_property_values(void **values, const t_argument *args)
{
	t_argument	*actual;
	size_t		index;

	if (!values)
		return ;
	index = 0;
	while (values[index])
	{
		actual = (t_argument *)(&args[index]);
		if (actual->array)
			free_property_array(values[index], actual);
		else if (actual->type == DT_STRUCT)
		{
			free_property_values(values[index],
				g_data_subtype_info[actual->subtype].fields);
		}
		else
			free(values[index]);
		index++;
	}
	free(values);
}

void	property_inputs_free(t_prop_inputs *inputs)
{
	if (!inputs)
		return ;
	free_tab((void **)inputs->argv);
	free_property_values(inputs->values, inputs->arguments);
	ft_memset(&inputs, 0, sizeof(t_prop_inputs));
}
