/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 17:53:21 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/07 02:46:45 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_parsing.h"

static inline void	handle_enclosers(char c, t_encloser_stack *stack,
						const char *enclosers)
{
	char	*pos;
	size_t	index;

	pos = ft_strchr(enclosers, c);
	if (!pos)
		return ;
	index = (size_t)(pos - enclosers);
	if (index % 2 == 0)
		stack_push(stack, enclosers[index + 1]);
	else if (!stack_empty(stack) && c == stack_peek(stack))
		stack_pop(stack);
}

static inline size_t	count_token(const char *str, const char *set,
			const char *enclosers)
{
	size_t				count;
	size_t				index;
	t_encloser_stack	stack;

	index = 0;
	count = 0;
	stack_init(&stack);
	while (str[index])
	{
		handle_enclosers(str[index], &stack, enclosers);
		if (stack_empty(&stack) && ft_strchr(set, str[index]))
			count++;
		index++;
	}
	return (count + 1);
}

static inline bool	token_allocate(size_t *wcount, size_t length,
						const char *start, char **tab)
{
	if (length > 0)
		tab[*wcount] = ft_substr(start, 0, length);
	else
		tab[*wcount] = ft_calloc(1, sizeof(char));
	if (!tab[*wcount])
	{
		*wcount = 0;
		free_tab((void **)tab);
		return (false);
	}
	(*wcount)++;
	return (true);
}

char	**tokenize(const char *str, const char *set,
			const char *enclosers, size_t *wcount)
{
	char				**result;
	size_t				start;
	size_t				index;
	t_encloser_stack	stack;

	stack_init(&stack);
	start = 0;
	index = 0;
	*wcount = 0;
	result = ft_calloc(count_token(str, set, enclosers) + 1, sizeof(char *));
	while (result)
	{
		handle_enclosers(str[index], &stack, enclosers);
		if (!str[index] || (stack_empty(&stack) && ft_strchr(set, str[index])))
		{
			if (!token_allocate(wcount, index - start, str + start, result))
				return (NULL);
			start = index + 1;
		}
		if (str[index] == '\0')
			break ;
		index++;
	}
	return (result);
}
