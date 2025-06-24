/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:58:06 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/24 16:16:48 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_itoab(int n, char *res, int len)
{
	unsigned int	u_n;
	int				digit_count;
	int				index;

	index = 0;
	u_n = n;
	if (n < 0)
	{
		res[len] = '-';
		len++;
		u_n = -n;
	}
	digit_count = ft_intlen(n);
	while (index < digit_count)
	{
		res[len + digit_count - 1 - index] = (u_n % 10) + '0';
		u_n /= 10;
		index++;
	}
	res[len + digit_count] = '\0';
}
