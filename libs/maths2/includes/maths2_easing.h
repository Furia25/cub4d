/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths2_easing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:56:28 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/04 22:52:52 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS2_EASING_H
# define MATHS2_EASING_H

#define _C1	1.70158f
#define _C2	2.5949f
#define _C3	2.70158f

extern double	lerp(double a, double b, double t);
extern double	step(double edge, double x);
extern double	smoothstep(double edge0, double edge1, double x);

/*
Easing headers implemented with https://easings.net 
formulas as they are implemented in postcss
*/

extern float	ease_quad_in(float t);
extern float	ease_quad_out(float t);
extern float	ease_quad_inout(float t);

extern float	ease_cubic_in(float t);
extern float	ease_cubic_out(float t);
extern float	ease_cubic_inout(float t);

extern float	ease_back_in(float t);
extern float	ease_back_out(float t);
extern float	ease_back_inout(float t);

extern float	ease_bounce_in(float t);
extern float	ease_bounce_out(float t);
extern float	ease_bounce_inout(float t);

#endif