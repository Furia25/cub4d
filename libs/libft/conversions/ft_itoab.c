/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:58:06 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/24 16:27:46 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_itoab(int n, wchar_t *res, int offset)
{
	unsigned int	u_n;
	int				digit_count;
	int				index;

	index = 0;
	u_n = n;
	if (n < 0)
	{
		res[offset++] = '-';
		u_n = -((long)n);
	}
	digit_count = ft_intlen(n);
	while (index < digit_count)
	{
		res[offset + digit_count - 1 - index] = (u_n % 10) + L'0';
		u_n /= 10;
		index++;
	}
	res[offset + digit_count] = L'\0';
}
