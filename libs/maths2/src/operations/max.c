/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:51:02 by val               #+#    #+#             */
/*   Updated: 2025/06/04 02:27:38 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

#ifndef _USE_STANDARD_MATH

double	fmax(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

float	fmaxf(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}
#endif
