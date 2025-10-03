/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 15:42:13 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/03 19:21:06 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_fdigit(int c)
{
	if (ft_isdigit(c) || c == '.' || c == '-')
		return (1);
	return (0);
}

t_prop_input	property_get_args(char *line, t_property_type type, t_game *game)
{
	t_prop_input	result;
	size_t		index;
	char		*temp;

	if (!line || *line == '\0')
		throw_error(ERROR_WTF, game);
	index = ft_strlen(g_property_token[type]);
	if (!line[index])
		throw_error_info(ERROR_PARSING_PROPERTY, line, game);
	temp = line + index;
	if (!str_remove_chars(temp, " \t\n"))
		throw_error_info(ERROR_PARSING_QUOTE, line, game);
	result.argc = count_words(temp, ',');
	result.argv = ft_split(temp, ',');
	if (!result.argv)
		throw_error(ERROR_PARSING_ALLOC, game);
	if (DEBUG_PARSING)
	{
		printf(DEBUG_PREFIX "%s : ", (char *)g_property_token[type]);
		print_char_tab(result.argv);
	}
	return (result);
}

bool	property_check_color(t_prop_input prop)
{
	size_t	index;
	char	*temp;
	int		temp_int;

	if (!prop.argv)
		return (false);
	index = 0;
	while (prop.argv[index])
	{
		temp = prop.argv[index];
		if (ft_strlen(temp) > 8)
			return (false);
		if (!ft_strcheck(temp, ft_isdigit))
			return (false);
		temp_int = ft_atoi(temp);
		if (index < 3 && (temp_int < 0 || temp_int > 255))
			return (false);
		if (index == 3 && (temp_int < 0 || temp_int >= PROPERTY_AMBIANT_MAX))
			return (false);
		index++;
	}
	return (true);
}

void	property_free(void *ptr)
{
	t_prop_input	*property;
	int			index;

	property = (t_prop_input *)ptr;
	if (!property)
		return ;
	if (property->argv)
	{
		index = 0;
		while (property->argv[index])
		{
			free(property->argv[index++]);
			property->argv[index] = NULL;
			index++;
		}
		free(property->argv);
	}
	free(property);
}
