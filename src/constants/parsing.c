/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:28:39 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/06 19:03:54 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_entities.h"
#include "cub3d_parsing.h"

const char						*g_data_type_info[DT_MAX] = {
[DT_INT] = "int",
[DT_FLOAT] = "float",
[DT_STRING] = "string",
[DT_UINT] = "uint",
[DT_STRUCT] = "struct",
[DT_ENUM] = "enum",
[DT_NULL] = "null",
};

const t_argument				g_dt_vec3[4] = {
{.name = "x", .type = DT_FLOAT},
{.name = "y", .type = DT_FLOAT},
{.name = "z", .type = DT_FLOAT},
};

static const char	*g_sdt_bool[] = {"false","true"};

static const char	*g_sdt_entity[ENTITY_MAX] = {
[ENTITY_NPC] = "NPC",
[ENTITY_DOOR] = "DOOR",
[ENTITY_TREE] = "TREE"
};


static const char	*g_sdt_door[5] = {
[0] = "DEFAULT",
[1] = "CHAIN",
[2] = "RANDOM"
};

const t_data_subtype_info		g_data_subtype_info[SDT_MAX] = {
[SDT_NULL] = {.name = NULL},
[SDT_VEC3] = {.name = "vec3", .fields = g_dt_vec3, .count = 3},
[SDT_BOOL] = {.name = "bool", .enum_values = g_sdt_bool, .count = 2},
[SDT_ENTITY] = {.name = "entity_type", .enum_values = g_sdt_entity, .count = ENTITY_MAX},
[SDT_DOOR] = {.name = "door_mode", .enum_values = g_sdt_door, .count = 3}
};
