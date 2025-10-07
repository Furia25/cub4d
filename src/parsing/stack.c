/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 02:40:58 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/07 04:52:25 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_structs.h"

void	stack_init(t_encloser_stack *s)
{
	s->top = 0;
}

bool	stack_empty(t_encloser_stack *s)
{
	return (s->top == 0);
}

void	stack_push(t_encloser_stack *s, char c)
{
	if (s->top < sizeof(s->data))
		s->data[s->top++] = c;
}

char	stack_pop(t_encloser_stack *s)
{
	if (s->top > 0)
		return (s->data[--s->top]);
	return ('\0');
}

char	stack_peek(t_encloser_stack *s)
{
	if (s->top > 0)
		return (s->data[s->top - 1]);
	return ('\0');
}
