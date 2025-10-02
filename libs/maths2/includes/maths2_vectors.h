/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths2_vectors.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 02:18:35 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/02 03:18:19 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS2_VECTORS_H
# define MATHS2_VECTORS_H

# include "private/maths2_vec2.h"
# include "private/maths2_vec3.h"

t_vec2	vec2_new(float x, float y);
t_vec3	vec3_new(float x, float y, float z);
t_vec3	vec2_to_vec3(t_vec2 v);
t_vec2	vec3_to_vec2(t_vec3 v);

#endif