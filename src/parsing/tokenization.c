/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 17:53:21 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/05 21:52:31 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_parsing.h"

static inline void	handle_enclosers(char c, bool *literal,
						size_t *current, const char *enclosers)
{
	char	*pos;
	size_t	index;

	if (c == '\0')
		return ;
	if (*literal)
	{
		if (c == enclosers[*current + 1])
		{
			*literal = false;
			*current = SIZE_MAX;
		}
		return ;
	}
	pos = ft_strchr(enclosers, c);
	if (!pos)
		return ;
	index = (size_t)(pos - enclosers);
	if (index % 2 != 0)
		return ;
	*literal = true;
	*current = pos - enclosers;
}

static inline size_t	count_token(const char *str, const char *set,
			const char *enclosers)
{
	size_t	count;
	size_t	index;
	size_t	current_literal;
	bool	literal;

	index = 0;
	count = 0;
	current_literal = SIZE_MAX;
	literal = false;
	while (str[index])
	{
		handle_enclosers(str[index], &literal, &current_literal, enclosers);
		if (!literal && ft_strchr(set, str[index]))
			count++;
		index++;
	}
	return (count + 1);
}

static inline bool	token_allocate(size_t *wcount, size_t length,
						const char *start, char **tab)
{
	tab[*wcount] = ft_substr(start, 0, length);
	if (!tab[*wcount])
	{
		*wcount = 0;
		free_tab((void **)tab);
		return (false);
	}
	(*wcount)++;
	return (true);
}

static inline void	init_tokenization(size_t *index, size_t *start,
						bool *literal, size_t *current_literal)
{
	*index = 0;
	*start = 0;
	*literal = false;
	*current_literal = SIZE_MAX;
}

char	**tokenize(const char *str, const char *set,
			const char *enclosers, size_t *wcount)
{
	char	**result;
	size_t	start;
	size_t	index;
	size_t	current_literal;
	bool	literal;

	if (!str || !set || !enclosers || !wcount)
		return (NULL);
	init_tokenization(&index, &start, &literal, &current_literal);
	*wcount = 0;
	result = ft_calloc(count_token(str, set, enclosers) + 1, sizeof(char *));
	while (result)
	{
		handle_enclosers(str[index], &literal, &current_literal, enclosers);
		if (!str[index] || (!literal && ft_strchr(set, str[index])))
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
