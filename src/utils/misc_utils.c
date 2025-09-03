/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:07:59 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/03 20:38:55 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "fcntl.h"

bool	is_file_valid(char *path)
{
	int	temp_fd;

	if (!path)
		return (false);
	temp_fd = open(path, O_RDONLY);
	if (temp_fd == -1)
		return (false);
	close(temp_fd);
	return (true);
}
