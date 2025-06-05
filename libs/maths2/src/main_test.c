/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:38:45 by val               #+#    #+#             */
/*   Updated: 2025/06/05 01:26:53 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <maths2.h>
#include "maths2_rng.h"

/*int	main(int argc, char **argv)
{
	t_rng_state	rng;

	if (argc != 3)
		return (EXIT_FAILURE);
	int	length = atoi(argv[1]);
	int height = atoi(argv[2]);
	uint64_t seed;
	FILE *fp = fopen("/dev/urandom", "rb");
	fread(&seed, 4, 1, fp);
	rng_init(&rng, seed);
	for (int y =0; y < height; y++)
	{
		for (int x = 0; x < length; x++)
		{
			printf("%d", rng_int_range(&rng, 0, 255));
			if (x != length - 1)
				printf(" ");
			dprintf(2, "LINE GENERATED %d/%d\n", y, height);
		}
		printf("\n");
	}
}*/

#include "maths2.h"
#include "maths2_geometry.h"

int main(void)
{
	t_rect t = rect_new(vec2_new(4, 5), vec2_new(50, 50));
	t.size.x += 1;
	printf("%f", t.size.x);
}
