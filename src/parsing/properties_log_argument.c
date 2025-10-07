/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties_log_argument.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:50:22 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/07 12:43:13 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parsing.h"
#include "ft_printf.h"

static inline void	print_struct_enum(int fd, bool verbose,
						const t_sdt_info *sub);

static inline void	print_array(int fd, const t_argument *arg)
{
	size_t	index;

	index = 0;
	while (index < arg->array)
	{
		ft_putstr_fd(ANSI_BRIGHT_MAGENTA, fd);
		if (arg->array_size != 0)
			ft_printf_fd(fd, "[%d]", arg->array_size);
		else if (arg->array)
			ft_putstr_fd("[]", fd);
		ft_putstr_fd(ANSI_RESET, fd);
		index++;
	}
}

void	print_argument(int fd, bool verbose, bool name, const t_argument *arg)
{
	const t_sdt_info	*sub = &g_data_subtype_info[arg->subtype];
	char				*type_name;

	if (arg->optional)
		ft_putchar_fd('<', fd);
	if (name)
		ft_printf_fd(fd, ANSI_BRIGHT_CYAN "%s" ANSI_RESET ": ", arg->name);
	if (sub->name != NULL)
		type_name = (char *)sub->name;
	else
		type_name = (char *)(g_data_type_info[arg->type]);
	ft_printf_fd(fd, ANSI_MAGENTA "%s" ANSI_RESET, type_name);
	if (verbose && sub->name)
		print_struct_enum(fd, verbose, sub);
	print_array(fd, arg);
	if (arg->limited && arg->type == DT_FLOAT)
		ft_printf_fd(fd, "(%d-%d)", (int)arg->fl_min, (int)arg->fl_max);
	else if (arg->limited)
		ft_printf_fd(fd, "(%d-%d)", arg->int_min, arg->int_max);
	if (arg->optional)
		ft_putstr_fd(ANSI_RESET ">", fd);
	ft_putstr_fd(ANSI_RESET, fd);
}

static inline void	print_struct_enum(int fd, bool verbose,
						const t_sdt_info *sub)
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
	ft_putchar_fd('{', fd);
	while (index < sub->count)
	{
		if (index > 0 && tab == sub->fields)
			ft_putstr_fd(", ", fd);
		else if (index > 0)
			ft_putstr_fd("|", fd);
		if (tab == sub->fields)
			print_argument(fd, verbose, true, (t_argument *)tab + index);
		else
			ft_putstr_fd(((char **)tab)[index], fd);
		index++;
	}
	ft_putchar_fd('}', fd);
}
