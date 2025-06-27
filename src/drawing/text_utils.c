/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:24:41 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/25 19:25:50 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glyphs.h"

size_t	strlen_wchar(wchar_t *str)
{
	size_t	index;

	index = 0;
	while (str[index])
		index++;
	return (index);
}
