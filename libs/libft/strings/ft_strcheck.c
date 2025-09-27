/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcheck.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 15:46:36 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/27 16:07:20 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_strcheck(char *str, int (*f)(int c))
{
	size_t	index;

	if (!str || !f)
		return (false);
	index = 0;
	while (str[index])
	{
		if (!f((unsigned char)str[index]))
			return (false);
		index++;
	}
	return (true);
}
