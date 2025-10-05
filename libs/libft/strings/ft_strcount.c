/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 04:49:32 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/05 04:50:50 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcount(const char *str, char c)
{
	size_t	index;
	size_t	count;

	index = 0;
	count = 0;
	while (str[index])
	{
		if (str[index] == c)
			count++;
		index++;
	}
	return (count);
}
