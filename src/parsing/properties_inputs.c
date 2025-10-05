/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties_inputs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 20:20:00 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/05 21:04:50 by vdurand          ###   ########.fr       */
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

t_error	property_check_delimiters(char *str)
{
	int		braces;
	int		brackets;

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
			return (ERROR_PROP_UNCLOSED_STRUCT);
		if (!check_delimiters(*str, '[', ']', &brackets))
			return (ERROR_PROP_UNCLOSED_ARRAY);
		str++;
	}
	return (ERROR_NONE);
}

void	property_check_argc(const t_property *property, t_prop_inputs *inputs,
			t_game *game)
{
	const size_t		length = arguments_count_required(property->args);

	if (inputs->argc < length)
		throw_error_property(property, ERROR_PROP_MISSING, game);
	if (!property->variable && inputs->argc > length)
		throw_error_property(property, ERROR_PROP_TOOMANY, game);
}

static inline void	handle_error(int exit_code,
						const t_property *property, t_game *game)
{
	if (exit_code == 0)
		return ;
	else if (exit_code == 1)
	{
		print_property_usage(2, property);
		exit_game(game);
	}
	else
		throw_error(ERROR_PARSING_ALLOC, game);
}

t_prop_inputs	property_get_inputs(char *line, t_property_type type,
					const t_property *property, t_game *game)
{
	t_prop_inputs	inputs;
	char			*temp;
	t_error			temp_error;
	int				exit_code;

	if (!property)
		throw_error(ERROR_PROP_INVALID, game);
	temp = line + ft_strlen(g_property_token[type]);
	temp_error = property_check_delimiters(temp);
	if (temp_error != ERROR_NONE)
		throw_error_property(property, temp_error, game);
	str_remove_chars(temp, " \t\n"),
	inputs.argv = tokenize(temp, TOKEN_DELIMITER,
		TOKEN_ENCLOSERS, &inputs.argc);
	print_char_tab(inputs.argv);
	if (!inputs.argv)
		throw_error(ERROR_PARSING_ALLOC, game);
	property_check_argc(property, &inputs, game);
	inputs.arguments = property->args;
	inputs.property = property;
	inputs.values = ft_calloc(inputs.argc + 1, sizeof(void *));
	if (!inputs.values)
		throw_error(ERROR_PARSING_ALLOC, game);
	exit_code = parse_arguments(1, inputs.values, property->args, inputs.argv);
	printf("%ld\n", inputs.argc);
	handle_error(exit_code, property, game);
	return (inputs);
}
