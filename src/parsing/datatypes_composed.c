/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datatypes_composed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 01:01:35 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/05 04:42:36 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_parsing.h"

t_error	handle_struct(int depth, char *pretoken, void **value, t_argument *arg)
{
	const t_data_subtype_info	*subtype = &g_data_subtype_info[arg->subtype];
	char						**tokens;
	size_t						arg_length;
	size_t						tokens_length;
	t_error						error;

	if (!prefix_check(false, pretoken, arg))
		return (ERROR_ARG_MALFORMED_STRUCT);
	arg_length = arguments_length(subtype->fields);
	*value = ft_calloc(arg_length, sizeof(void *));
	if (!(*value))
		return (ERROR_PARSING_ALLOC);
	tokens = tokenize(pretoken, TOKEN_DELIMITER,
		TOKEN_ENCLOSERS, &tokens_length);
	if (!tokens)
		return (ERROR_PARSING_ALLOC);
	if (arg_length != tokens_length)
	{
		free_chartab(tokens);
		return (ERROR_ARG_INCOMPLETE);
	}
	error = parse_arguments(depth + 1, *value,
		subtype->fields, tokens);
	free_chartab(tokens);
	return (error);
}

t_error	handle_array(int depth, char *pretoken, void **value, t_argument *arg)
{
	char	**tokens;
	size_t	length;
	t_error	error;

	if (!prefix_check(true, pretoken, arg))
		return (ERROR_ARG_MALFORMED_STRUCT);
	tokens = tokenize(pretoken, TOKEN_DELIMITER, TOKEN_ENCLOSERS, &length);
	if (!tokens)
		return (ERROR_PARSING_ALLOC);
	if (arg->array_size != 0 && length != arg->array_size)
	{
		free_chartab(tokens);
		return (ERROR_ARG_ARRAY_SIZE);
	}
	*value = ft_calloc(arg->array_size, sizeof(void *));
	if (!(*value))
	{
		free_chartab(tokens);
		return (ERROR_ARG_ARRAY_SIZE);
	}
	error = parse_arguments(depth + 1, *value, arg, tokens);
	free_chartab(tokens);
	return (error);
}

t_error	handle_enum(char *token, void **value, t_argument *arg)
{
	const t_data_subtype_info	*subtype = &g_data_subtype_info[arg->subtype];
	size_t						index;

	if (!subtype->enum_values)
		return (ERROR_ARG_INVALID);
	index = 0;
	while (index < subtype->count)
	{
		if (ft_strcmp(subtype->enum_values[index], token) == 0)
		{
			*value = ft_calloc(1, sizeof(size_t));
			if (!(*value))
				return (ERROR_PARSING_ALLOC);
			*((size_t *)(*value)) = index;
			return (ERROR_NONE);
		}
		index++;
	}
	return (ERROR_ARG_INVALID);
}
