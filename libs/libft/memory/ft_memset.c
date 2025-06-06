/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:52:43 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/06 00:09:33 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdint.h"

void	*memset_fast(void *ptr, int value, size_t num)
{
	unsigned char	*p;
	unsigned char	val;
	uint64_t		val64;

	val = (unsigned char)value;
	p = ptr;
	while (((uintptr_t)p & 7) && num--)
		*p++ = val;
	val64 = (uint64_t)val | ((uint64_t)val << 8) | ((uint64_t)val << 16) \
	| ((uint64_t)val << 24) | ((uint64_t)val << 48) | ((uint64_t)val << 56);
	while (num >= 8)
	{
		*(uint64_t *)p = val64;
		p += 8;
		num -= 8;
	}
	while (num--)
		*p++ = val;
	return (ptr);
}

/* int main () 
{
   char str[50];

   strcpy(str, "Welcome to Tutorialspoint");
   puts(str);

   ft_memset(str, '#', 7);
   puts(str);
   
   return(0);
} */