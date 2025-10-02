/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_methods.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:28:13 by vdurand           #+#    #+#             */
/*   Updated: 2025/08/20 18:21:13 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "libft.h"

bool	vector_append(t_vector *vec, void *value)
{
	if (!vec)
		return (false);
	if (vec->total + 1 > vec->size)
	{
		if (!vec->resize(vec, vec->size * 2))
			return (false);
	}
	vec->items[vec->total] = value;
	vec->total++;
	return (true);
}

bool	vector_insert(t_vector *vec, void *value, unsigned int index)
{
	if (!vec)
		return (false);
	if (vec->total + 1 > vec->size)
	{
		if (!vec->resize(vec, vec->size * 2))
			return (false);
	}
	if (index < vec->total)
	{
		ft_memmove(vec->items + index + 1, vec->items + index,
			(vec->total - index) * sizeof(void *));
	}
	vec->items[index] = value;
	vec->total++;
	return (true);
}

bool	vector_remove(t_vector *vec, unsigned int index)
{
	void	*value;

	if (!vec)
		return (false);
	value = vec->get(vec, index);
	if (value == NULL)
		return (false);
	vec->val_free(value);
	value = NULL;
	if (index != vec->total - 1)
	{
		ft_memmove(vec->items + index, vec->items + index + 1,
			(vec->total - index - 1) * sizeof(void *));
	}
	vec->total--;
	if (vec->total <= vec->size * 0.25 && !vec->resize(vec, vec->size * 0.5))
		return (false);
	return (true);
}

void	vector_iter(t_vector *vec, void (*f)(void *))
{
	size_t	i;
	void	*value;

	if (!vec)
		return ;
	i = 0;
	while (i < vec->total)
	{
		value = vec->items[i];
		if (value == NULL)
			break ;
		f(value);
		i++;
	}
}

void	*vector_get(t_vector *vec, unsigned int index)
{
	if (!vec)
		return (NULL);
	if (index >= vec->total)
		return (NULL);
	return (vec->items[index]);
}
