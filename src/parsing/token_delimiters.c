/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_delimiters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 03:49:07 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/06 03:59:53 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_delimiters(char c, char open, char close, int *count)
{
	if (c == open)
		(*count)++;
	else if (c == close)
		(*count)--;
	if (*count < 0)
		return (false);
	return (true);
}

t_error	token_check_delimiters(char *str)
{
	int	braces;
	int	brackets;

	if (!str || *str == '\0')
		return (ERROR_PROP_INVALID);
	braces = 0;
	brackets = 0;
	while (str && *str)
	{
		if (*str == '"')
		{
			str++;
			while (*str && *str != '"')
				str++;
			if (*str == '\0')
				return (ERROR_PROP_UNCLOSED_QUOTE);
		}
		if (!check_delimiters(*str, '{', '}', &braces))
			return (ERROR_PROP_UNEXPECTED_CLOSING_STRUCT);
		if (!check_delimiters(*str, '[', ']', &brackets))
			return (ERROR_PROP_UNEXPECTED_CLOSING_ARRAY);
		str++;
	}
	if (braces != 0)
		return (ERROR_PROP_UNCLOSED_STRUCT);
	if (brackets != 0)
		return (ERROR_PROP_UNCLOSED_ARRAY); 
	return (ERROR_NONE);
}
