/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   composed_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 01:01:35 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/05 01:59:40 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_parsing.h"

t_error	handle_struct(size_t index, int depth,
			t_argument *arg, t_prop_input *input)
{
	const t_data_subtype_info	*subtype = &g_data_subtype_info[arg->subtype];
	char						**tokens;
	size_t						arg_length;
	size_t						tokens_length;
	t_error						error;

	if (!prefix_check(input->argv[index], arg))
		return (ERROR_ARG_MALFORMED_STRUCT);
	arg_length = arguments_length(subtype->fields);
	input->values[index] = ft_calloc(arg_length, sizeof(void *));
	if (!input->values[index])
		return (ERROR_PARSING_ALLOC);
	tokens = tokenize(input->argv[index], TOKEN_DELIMITER,
		TOKEN_ENCLOSERS, &tokens_length);
	if (!tokens)
		return (ERROR_PARSING_ALLOC);
	if (arg_length != tokens_length)
	{
		free_chartab(tokens);
		return (ERROR_ARG_INCOMPLETE);
	}
	error = parse_arguments(depth + 1, &input->values[index],
		subtype->fields, tokens);
	free_chartab(tokens);
	return (error);
}
