/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:15:50 by val               #+#    #+#             */
/*   Updated: 2025/06/06 18:40:44 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS2_H
# define MATHS2_H
# include "stdbool.h"

# define STANDALONE_IMPLEMENTATION	0

# if STANDALONE_IMPLEMENTATION == 1
#  define _USE_STANDALONE_MATH
# endif

# ifndef _USE_STANDALONE_MATH
#  ifdef __has_include
#   if __has_include(<math.h>)
#    include <math.h>
#   endif
#  endif
# endif

# ifdef _MATH_H
#  define _USE_STANDARD_MATH	1
# endif

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define _FLOAT_EPSILON 1e-6f
# define _DOUBLE_EPSILON 1e-12

extern double		deg_to_rad(double deg);
extern double		rad_to_deg(double rad);

extern double		m2_invsqrt(double number);
extern double		m2_sqrt(double x);

extern int			clamp(int x, int min, int max);
extern double		dclamp(double x, double min, double max);
extern float		fclamp(float x, float min, float max);

extern int			max(int a, int b);
extern int			min(int a, int b);

extern int			sign(double x);
extern int			m2_abs(int x);
extern int			normalize(int x, int min, int max);
extern double		dnormalize(double x, double min, double max);
extern bool			double_equal(double a, double b);
extern bool			float_equal(float a, float b);

# ifndef _USE_STANDARD_MATH

extern double		fmax(double a, double b);
extern float		fmaxf(float a, float b);
extern double		fmin(double a, double b);
extern float		fminf(float a, float b);
extern float		fabsf(float x);
extern double		fabs(double x);
# else

extern double		round_to(double x, double step);

# endif

#endif