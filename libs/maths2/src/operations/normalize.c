/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 02:43:14 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/04 02:43:22 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	normalize(int x, int min, int max)
{
	return ((x - min) / (max - min));
}

double	dnormalize(double x, double min, double max)
{
	return ((x - min) / (max - min));
}
