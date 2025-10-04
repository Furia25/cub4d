/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties_inputs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 20:20:00 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/04 19:55:02 by vdurand          ###   ########.fr       */
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

t_error	property_check_inputes(char *str)
{
	t_error	result;
	int		braces;
	int		brackets;

	braces = 0;
	brackets = 0;
	result = ERROR_NONE;
	while (str && *str)
	{
		if (*str == '"')
		{
			str++;
			while (*str != '"')
				str++;
			if (*str == '\0')
				return (ERROR_PROP_UNCLOSED_QUOTE);
		}
		if (!check_delimiters(*str, '{', '}', &braces))
			return (ERROR_PROP_UNCLOSED_STRUCT);
		if (!check_delimiters(*str, '[', ']', &brackets))
			return (ERROR_PROP_UNCLOSED_ARRAY);
		str++;
	}
	return (ERROR_NONE);
}

t_prop_input	property_get_inputs(char *line, t_property_type type,
					t_property *property, t_game *game)
{
	t_prop_input	result;
	size_t			index;
	char			*temp;
	t_error			temp_error;

	index = ft_strlen(g_property_token[type]);
	temp = line + index;
	temp_error = property_check_inputes(temp);
	if (temp_error != ERROR_NONE)
		throw_error_property(property, temp_error, game);
	str_remove_chars(temp, " \t\n"),
	result.argv = tokenize(temp, ",", "[]{}\"", &result.argc);
	if (!result.argv)
		throw_error(ERROR_PARSING_ALLOC, game);
	if (DEBUG_PARSING)
	{
		printf(DEBUG_PREFIX "%s : ", (char *)g_property_token[type]);
		print_char_tab(result.argv);
	}
	return (result);
}
