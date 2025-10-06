/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 17:53:21 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/06 03:09:34 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_parsing.h"

static inline void	handle_enclosers(char c, size_t *depth,
						size_t *current, const char *enclosers)
{
	char	*pos;
	size_t	index;

	if (c == '\0')
		return ;
	pos = ft_strchr(enclosers, c);
	if (!pos)
		return ;
	index = (size_t)(pos - enclosers);
	if (index % 2 == 0)
	{
		if (*depth == 0)
			*current = index;
		(*depth)++;
	}
	else if (*depth > 0 && index == *current + 1)
	{
		(*depth)--;
		if (*depth == 0)
			*current = SIZE_MAX;
	}
}

static inline size_t	count_token(const char *str, const char *set,
			const char *enclosers)
{
	size_t	count;
	size_t	index;
	size_t	current_encloser;
	size_t	depth;

	index = 0;
	count = 0;
	current_encloser = SIZE_MAX;
	depth = 0;
	while (str[index])
	{
		handle_enclosers(str[index], &depth, &current_encloser, enclosers);
		if (!depth && ft_strchr(set, str[index]))
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
						size_t *depth, size_t *current_encloser)
{
	*index = 0;
	*start = 0;
	*depth = 0;
	*current_encloser = SIZE_MAX;
}

char	**tokenize(const char *str, const char *set,
			const char *enclosers, size_t *wcount)
{
	char	**result;
	size_t	start;
	size_t	index;
	size_t	current_encloser;
	size_t	depth;

	init_tokenization(&index, &start, &depth, &current_encloser);
	*wcount = 0;
	result = ft_calloc(count_token(str, set, enclosers) + 1, sizeof(char *));
	if (!result)
		return (NULL);
	while (1)
	{
		handle_enclosers(str[index], &depth, &current_encloser, enclosers);
		if (!str[index] || (depth == 0 && ft_strchr(set, str[index])))
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
