/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_managing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:48:38 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/01 10:26:10 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_png.h"
#include <errno.h>

static bool			verify_png_signature(t_cp_file *file);
static bool			assign_basics(t_png *png, char *file_name);
static inline void		png_clean(t_png *png);

t_png	*png_open(char *file_name)
{
	t_png		*png;

	png = ft_calloc(1, sizeof(t_png));
	if (!png)
		return (NULL);
	if (!assign_basics(png, file_name))
	{
		png_close(png);
		return (NULL);
	}
	png->convert_endian = ft_isbigendian();
	if (!verify_png_signature(png->file) || !png_parse(png))
	{
		png_close(png);
		return (NULL);
	}
	png_clean(png);
	return (png);
}

static inline void	png_clean(t_png *png)
{
	cp_buffer_reset(&png->compressed_data);
	cp_buffer_reset(&png->data);
	cp_close(png->file);
	png->file = NULL;
}

void	png_close(t_png *png)
{
	if (!png)
		return ;
	png_clean(png);
	free(png->palette);
	free(png->pixels_8bit);
	free(png);
}

static bool	assign_basics(t_png *png, char *file_name)
{
	t_cp_file	*file;

	file = cp_open(file_name, O_RDONLY);
	if (!file)
		return (false);
	png->file = file;
	return (true);
}

static bool	verify_png_signature(t_cp_file *file)
{
	uint64_t	signature;

	if (cp_fread(&signature, sizeof(uint64_t), 1, file) != 1)
		return (false);
	if (ft_memcmp(&signature, PNG_SIGNATURE, sizeof(uint64_t)) == 0)
	{
		return (true);
	}
	else
	{
		ft_putstr_fd(PNG_ERROR_SIGNATURE, 2);
		return (false);
	}
}
