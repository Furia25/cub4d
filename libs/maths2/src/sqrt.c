/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sqrt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:34:17 by val               #+#    #+#             */
/*   Updated: 2025/06/04 01:55:58 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths2_utils.h"

double	m2_invsqrt(double number)
{
	t_64_cast	conv;
	double		y;
	double		halfx;

	halfx = number * 0.5;
	conv.d = number;
	conv.u = 0x5FE6EB50C7B537A9ULL - (conv.u >> 1);
	y = conv.d;
	y = y * (1.5 - (halfx * y * y));
	y = y * (1.5 - (halfx * y * y));
	return (y);
}

double	m2_sqrt(double x)
{
	return (x * m2_invsqrt(x));
}
