/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:27:56 by vdurand           #+#    #+#             */
/*   Updated: 2025/08/18 19:32:37 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stdlib.h>
# include <stdbool.h>

# define VECTOR_BASE_SIZE	6

typedef struct s_vector t_vector;
struct s_vector
{
	void			**items;
	unsigned int	total;
	unsigned int	size;
	bool			(*insert)(t_vector *self, void *value, unsigned int index);
	bool			(*append)(t_vector *self, void *value);
	bool			(*remove)(t_vector *self, unsigned int index);
	bool			(*resize)(t_vector *self, unsigned int size);
	void			*(*get)(t_vector *self, unsigned int index);
	void			(*free)(t_vector *self, bool content);
	void			(*val_free)(void *val);
	void			(*iter)(t_vector *self, void (*f)(void *));
};

t_vector	*vector_init(t_vector *vector);
t_vector	*vector_new(void);
void		vector_free(t_vector *vec, bool content);
bool		vector_resize(t_vector *vec, unsigned int size);
void		*vector_get(t_vector *vec, unsigned int index);
void		vector_iter(t_vector *vec, void (*f)(void *));
bool		vector_append(t_vector *vec, void *value);
bool		vector_remove(t_vector *vec, unsigned int index);
bool		vector_insert(t_vector *vec, void *value, unsigned int index);

#endif