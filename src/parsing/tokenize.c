/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 17:53:21 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/04 19:24:53 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parsing.h"

static inline size_t	count_token(const char *str, const char *set,
			const char *enclosers)
{
	size_t	count;
	size_t	index;
	char	current_literal;
	bool	literal;

	index = 0;
	count = 0;
	literal = false;
	while (str[index])
	{
		if (!literal && ft_strchr(set, str[index]))
			count++;
		else if (ft_strchr(enclosers, str[index]))
		{
			if (!literal)
			{
				literal = true;
				current_literal = str[index];
			}
			else if (current_literal == str[index])
				literal = false;
		}
		index++;
	}
	return (count + 1);
}

static inline void	handle_enclosers(char c, bool *literal,
						char *current, const char *enclosers)
{
	if (ft_strchr(enclosers, c))
	{
		if (*literal == false)
		{
			*literal = true;
			*current = c;
		}
		else if (*current == c)
			*literal = false;
	}
}

static inline bool	token_allocate(size_t *wcount, size_t length,
						char *start, char **tab)
{
	tab[*wcount] = ft_substr(start, 0, length);
	if (!tab[*wcount])
	{
		free_chartab(tab);
		return (false);
	}
	(*wcount)++;
	return (true);
}

static inline void	init_tokenization(size_t *index, size_t *start,
						bool *literal, char *current_literal)
{
	*index = 0;
	*start = 0;
	*literal = false;
	*current_literal = '\0';
}

char	**tokenize(const char *str, const char *set,
			const char *enclosers, size_t *wcount)
{
	char	**result;
	char	current_literal;
	bool	literal;
	size_t	start;
	size_t	index;

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
