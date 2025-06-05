/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:51:02 by val               #+#    #+#             */
/*   Updated: 2025/06/04 02:04:19 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

#ifndef _USE_STANDARD_MATH

double	fmin(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

float	fminf(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}
#endif
