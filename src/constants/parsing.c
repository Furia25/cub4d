/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:28:39 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/05 17:31:10 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_entities.h"
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

static const char	*g_dt_entity[ENTITY_MAX] = {
[ENTITY_NPC] = "NPC",
[ENTITY_DOOR] = "DOOR",
[ENTITY_TREE] = "TREE"
};

const t_data_subtype_info		g_data_subtype_info[SDT_MAX] = {
[SDT_NULL] = {.name = NULL},
[SDT_VEC3] = {.name = "vec3", .fields = g_dt_vec3, .count = 3},
[SDT_BOOL] = {.name = "bool", .enum_values = g_dt_bool, .count = 2},
[SDT_ENTITY] = {.name = "type", .enum_values = g_dt_entity, .count = ENTITY_MAX - 1}
};
