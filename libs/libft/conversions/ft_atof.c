/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:24:29 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/13 18:50:33 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errno.h"
#include "libft.h"
#include "stdio.h"

static inline int	return_invalid(void)
{
	errno = EINVAL;
	return (0);
}

static inline bool	init(char **str, int *sign)
{
	*sign = 1;
	if (!(*str))
		return (return_invalid());
	while (*str && ft_isspace(**str))
		(*str)++;
	while (*str && (**str == '+' || **str == '-'))
	{
		if (**str == '-')
			(*sign) = -(*sign);
		(*str)++;
	}
	return (true);
}

static inline void	add_digit(char digit, double *result,
	double *scale, bool afterdot)
{
	if (afterdot)
	{
		*scale = (*scale) / 10;
		*result += (digit - '0') * (*scale);
	}
	else
		*result = *result * 10 + (digit - '0');
}

double	ft_atof(char *str)
{
	double	result;
	int		sign;
	int		afterdot;
	double	scale;

	if (!init(&str, &sign))
		return (0);
	result = 0;
	scale = 1;
	afterdot = 0;
	while (str && ((*str >= '0' && *str <= '9') || *str == '.'))
	{
		if (*str != '.')
			add_digit(*str, &result, &scale, afterdot);
		else
			afterdot++;
		if (afterdot > 1)
			return (return_invalid());
		str++;
	}
	return (result * sign);
}
