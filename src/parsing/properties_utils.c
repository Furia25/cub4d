/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 15:42:13 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/30 19:04:41 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_property	property_get_args(char *line, t_property_type type, t_game *game)
{
	t_property	result;
	size_t		index;
	char		*temp;

	if (!line || *line == '\0')
		throw_error(game, ERROR_WTF);
	index = ft_strlen(g_property_token[type]);
	if (!line[index])
		throw_error_info(game, ERROR_PARSING_PROPERTY, line);
	temp = line + index;
	str_remove_chars(temp, " \t\n");
	result.argc = count_words(temp, ',');
	result.argv = ft_split(temp, ',');
	if (!result.argv)
		throw_error(game, ERROR_PARSING_ALLOC);
	if (DEBUG_PARSING)
	{
		printf(DEBUG_PREFIX "%s : ", (char *)g_property_token[type]);
		print_char_tab(result.argv);
	}
	return (result);
}

bool	property_check_color(t_property prop)
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
			return false;
		if (index == 3 && (temp_int < 0 || temp_int >= PROPERTY_AMBIANT_MAX))
			return false;
		index++;
	}
	return (true);
}

void	property_free(void *ptr)
{
	t_property	*property;
	int			index;

	property = (t_property *)ptr;
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
