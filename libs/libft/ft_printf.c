/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:14:00 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/29 01:29:30 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	ap;
	size_t	sum;

	if (!format)
		return (-1);
	va_start(ap, format);
	sum = ft_vprintf_fd(fd, format, ap);
	va_end(ap);
	return (sum);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	size_t	sum;

	if (!format)
		return (-1);
	va_start(ap, format);
	sum = ft_vprintf_fd(1, format, ap);
	va_end(ap);
	return (sum);
}
