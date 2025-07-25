/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:26:08 by val               #+#    #+#             */
/*   Updated: 2025/07/25 14:09:38 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths2.h"

#ifdef _USE_STANDARD_MATH

double	round_to(double x, double step)
{
	return (floor(x / step + 0.5) * step);
}

#endif

bool	double_equal(double a, double b)
{
	return (fabs(a - b) < _DOUBLE_EPSILON);
}

bool	float_equal(float a, float b)
{
	return (fabsf(a - b) < _FLOAT_EPSILON);
}
