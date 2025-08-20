/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_managing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:27:40 by vdurand           #+#    #+#             */
/*   Updated: 2025/08/20 18:18:39 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
# include "libft.h"

t_vector	*vector_init(t_vector *vector)
{
	if (!vector)
		return (NULL);
	vector->items = ft_calloc(VECTOR_BASE_SIZE, sizeof(void *));
	if (!vector->items)
		return (NULL);
	vector->size = VECTOR_BASE_SIZE;
	vector->total = 0;
	vector->resize = vector_resize;
	vector->get = vector_get;
	vector->free = vector_free;
	vector->val_free = free;
	vector->iter = vector_iter;
	vector->append = vector_append;
	vector->remove = vector_remove;
	vector->insert = vector_insert;
	vector->get_index = vector_get_index;
	return (vector);
}

t_vector	*vector_new(void)
{
	t_vector	*result;

	result = malloc(sizeof(t_vector));
	if (!result)
		return (NULL);
	if (!vector_init(result))
	{
		free(result);
		return (NULL);
	}
	return (result);
}

void	vector_free(t_vector *vec, bool content)
{
	if (!vec)
		return ;
	if (content)
		vec->iter(vec, vec->val_free);
	free(vec->items);
	free(vec);
}

bool	vector_resize(t_vector *vec, unsigned int size)
{
	void	**temp;

	if (!vec)
		return (false);
	if (size < VECTOR_BASE_SIZE)
		return (true);
	if (size < vec->total)
		size = vec->total;
	temp = ft_calloc(size, sizeof(void *));
	if (!temp)
		return (false);
	ft_memcpy(temp, vec->items, vec->total * sizeof(void *));
	free(vec->items);
	vec->items = temp;
	vec->size = size;
	return (true);
}
