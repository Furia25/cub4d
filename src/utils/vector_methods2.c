/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_methods2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:11:32 by vdurand           #+#    #+#             */
/*   Updated: 2025/08/20 18:16:08 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

long	vector_get_index(t_vector *vec, void *value)
{
	size_t	i;
	void	*current;

	if (!vec)
		return (-1);
	if (!value)
		return (-1);
	i = 0;
	while (i < vec->total)
	{
		current = vec->items[i];
		if (current == NULL)
			break ;
		if (current == value)
			return (i);
		i++;
	}
	return (-1);
}
