/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:28:39 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/04 15:31:06 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parsing.h"

const t_data_type_info			g_data_type_info[DT_MAX] = {
[DT_INT] = {"int", sizeof(int)},
[DT_FLOAT] = {"float", sizeof(float)},
[DT_STRING] = {"string", sizeof(char *)},
[DT_STRUCT] = {"struct", 0},
[DT_ENUM] = {"enum", 0},
[DT_NULL] = {"null", 0}
};

const t_argument				g_dt_vec3[4] = {
{.name = "x", .type = DT_FLOAT},
{.name = "y", .type = DT_FLOAT},
{.name = "z", .type = DT_FLOAT},
};

static const char	*g_dt_bool[] = {"false","true"};

const t_data_subtype_info		g_data_subtype_info[SDT_MAX] = {
[SDT_NULL] = {.name = NULL},
[SDT_VEC3] = {.name = "vec3", .fields = g_dt_vec3, .count = 3},
[SDT_BOOL] = {.name = "bool", .enum_values = g_dt_bool, .count = 2}
};
