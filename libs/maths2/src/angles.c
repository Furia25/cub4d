/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 02:31:44 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/04 02:42:04 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths2.h"

double	deg_to_rad(double deg)
{
	return (deg * (M_PI / 180.0));
}

double	rad_to_deg(double rad)
{
	return (rad * (180.0 / M_PI));
}
