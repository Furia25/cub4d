/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths2_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:56:15 by val               #+#    #+#             */
/*   Updated: 2025/06/03 22:20:46 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS2_UTILS_H
# define MATHS2_UTILS_H
# include <stdint.h>

typedef union u_32cast
{
	float		f;
	int32_t		u;
}	t_32_cast;

typedef union u_64cast
{
	double		d;
	int64_t		u;
}	t_64_cast;

#endif