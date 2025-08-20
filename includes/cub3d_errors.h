/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_errors.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:33:43 by vdurand           #+#    #+#             */
/*   Updated: 2025/08/20 18:34:59 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_ERRORS_H
# define CUB3D_ERRORS_H

# define ERROR_BASIC	"Game crashed unamed error."

typedef enum e_error
{
	ERROR_LOADING_ASSETS,
	ERROR_LOADING_GRAPHICS,
	ERROR_LOADING,
	ERROR_WINDOW,
	ERROR_MAX
}	t_error;
#endif