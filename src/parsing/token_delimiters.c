/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_delimiters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 03:49:07 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/07 05:29:07 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static inline t_error	get_unclosed_error(t_encloser_stack *stack)
{
	char	top;

	top = stack_peek(stack);
	if (top == '"')
		return (ERROR_PROP_UNCLOSED_QUOTE);
	if (top == '}')
		return (ERROR_PROP_UNCLOSED_STRUCT);
	if (top == ']')
		return (ERROR_PROP_UNCLOSED_ARRAY);
	return (ERROR_PROP_INVALID);
}

static inline t_error	check_stack(char c, t_encloser_stack *stack)
{
	if (c == '"')
		stack_push(stack, '"');
	else if (c == '{')
		stack_push(stack, '}');
	else if (c == '[')
		stack_push(stack, ']');
	else if (c == '}')
	{
		if (stack_empty(stack) || stack_peek(stack) != '}')
			return (ERROR_PROP_UNEXPECTED_CLOSING_STRUCT);
		stack_pop(stack);
	}
	else if (c == ']')
	{
		if (stack_empty(stack) || stack_peek(stack) != ']')
			return (ERROR_PROP_UNEXPECTED_CLOSING_ARRAY);
		stack_pop(stack);
	}
	return (ERROR_NONE);
}

t_error	token_check_delimiters(char *str)
{
	t_encloser_stack	stack;
	t_error				temp_error;
	char				c;

	if (!str || *str == '\0')
		return (ERROR_PROP_INVALID);
	stack_init(&stack);
	while (*str)
	{
		c = *str;
		if (!stack_empty(&stack) && stack_peek(&stack) == '"')
		{
			if (c == '"')
				stack_pop(&stack);
			str++;
			continue ;
		}
		temp_error = check_stack(c, &stack);
		if (temp_error != ERROR_NONE)
			return (temp_error);
		str++;
	}
	if (!stack_empty(&stack))
		return (get_unclosed_error(&stack));
	return (ERROR_NONE);
}
