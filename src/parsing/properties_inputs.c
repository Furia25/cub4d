/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties_inputs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 20:20:00 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/07 04:50:11 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	property_check_argc(const t_property *property,
			t_prop_inputs *inputs, t_game *game)
{
	const size_t		max_length = arguments_length(property->args);
	const size_t		min_length = arguments_count_required(property->args);

	if (inputs->argc < min_length)
		throw_error_property(property, ERROR_PROP_MISSING, game);
	if (!property->variable && inputs->argc > max_length)
		throw_error_property(property, ERROR_PROP_TOOMANY, game);
	inputs->vla = false;
}

void	property_handle_error(t_prop_inputs *inputs, t_error error,
			const t_property *property, t_game *game)
{
	if (error == ERROR_NONE)
		return ;
	else if (error != ERROR_PARSING_ALLOC)
	{
		print_property_error(game->parsing.line_num,
			ERROR_PROP_INVALID, property);
		argument_queue_print();
		print_property_usage(2, property);
		if (inputs->vla)
			property_inputs_free(inputs);
		exit_game(game);
	}
	else
	{
		if (inputs->vla)
			property_inputs_free(inputs);
		throw_error(ERROR_PARSING_ALLOC, game);
	}
}

void	property_get_inputs(char *line, t_property_type type,
					const t_property *property, t_game *game)
{
	t_prop_inputs		*inputs;
	char				*temp;
	t_error				temp_error;
	t_error				error;

	inputs = &game->parsing.temp_inputs;
	temp = line + ft_strlen(g_property_token[type]);
	temp_error = token_check_delimiters(temp);
	if (temp_error != ERROR_NONE)
		throw_error_property(property, temp_error, game);
	str_remove_chars(temp, " \t\n");
	inputs->argv = tokenize(temp, TOKEN_DELIMITER,
			TOKEN_ENCLOSERS, &inputs->argc);
	if (!inputs->argv)
		throw_error(ERROR_PARSING_ALLOC, game);
	property_check_argc(property, inputs, game);
	if (inputs->argc == 0)
		return ;
	inputs->arguments = property->args;
	inputs->property = property;
	inputs->values = ft_calloc(inputs->argc + 1, sizeof(void *));
	if (!inputs->values)
		throw_error(ERROR_PARSING_ALLOC, game);
	error = parse_arguments(1, inputs->values, property->args, inputs->argv);
	property_handle_error(inputs, error, property, game);
}

t_prop_inputs	property_get_vla(t_prop_inputs *inputs,
					const t_property *property, t_game *game)
{
	t_prop_inputs	result;
	size_t			length;
	t_error			error;

	result = *inputs;
	length = arguments_length(inputs->arguments);
	result.argc -= length;
	result.argv += length;
	result.values += length;
	property_check_argc(property, &result, game);
	result.arguments = property->args;
	result.property = property;
	result.vla = true;
	error = parse_arguments(1, result.values, property->args, result.argv);
	property_handle_error(&result, error, property, game);
	return (result);
}
