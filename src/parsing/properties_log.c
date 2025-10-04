/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_log.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:50:22 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/04 18:44:21 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parsing.h"
#include "stdlib.h"
#include "stdbool.h"
#include "stdio.h"

static inline void	print_struct_enum(bool verbose,
						const t_data_subtype_info *sub);

void	print_argument(bool verbose, const t_argument *arg)
{
	const t_data_subtype_info	*sub = &g_data_subtype_info[arg->subtype];

	write(1, '<', arg->optional);
	printf("%s: ", arg->name);
	if (sub->name != NULL)
	{
		printf("%s ", sub->name);
		if (verbose)
			print_struct_enum(verbose, sub);
	}
	else
		ft_putstr_fd(g_data_type_info[arg->type].name, 1);
	if (arg->array && arg->array_size != 0)
		printf("[%zu]", arg->array_size);
	else if (arg->array)
		ft_putstr_fd("[]", 1);
	if (arg->limited)
	{
		if (arg->type == DT_INT)
			printf("(%d-%d)", arg->int_min, arg->int_max);
		else if (arg->type == DT_FLOAT)
			printf("(%f-%f)", arg->fl_min, arg->fl_max);
	}
	write(1, '<', arg->optional);
}

static inline void	print_struct_enum(bool verbose,
						const t_data_subtype_info *sub)
{
	size_t		index;
	const void	*tab;

	if (sub->fields)
		tab = sub->fields;
	else if (sub->enum_values)
		tab = sub->enum_values;
	else
		return ;
	index = 0;
	while (index < sub->count)
	{
		if (index > 0 && tab == sub->fields)
			ft_putstr_fd(", ", 1);
		else if (index > 0)
			ft_putstr_fd(", ", 1);
		if (tab == sub->fields)
			print_argument(verbose, (t_argument *)tab + index);
		else
			ft_putstr_fd((char *)tab + index, 1);
		index++;
	}
}
