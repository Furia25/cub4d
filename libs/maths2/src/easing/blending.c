/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blending.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 02:46:25 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/04 16:16:35 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	lerp(double a, double b, double t)
{
	return (a + (b - a) * t);
}

double	step(double edge, double x)
{
	if (x < edge)
		return (0.0);
	return (1.0);
}

double	smoothstep(double edge0, double edge1, double x)
{
	double	t;

	if (x <= edge0)
		return (0.0);
	if (x >= edge1)
		return (1.0);
	t = (x - edge0) / (edge1 - edge0);
	return (t * t * (3.0 - 2.0 * t));
}
