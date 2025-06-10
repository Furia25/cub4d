# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/13 23:20:17 by val               #+#    #+#              #
#    Updated: 2025/06/10 18:55:22 by vdurand          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	ANSI TEXT COLORS
BLACK = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
WHITE = \033[37m

#	ANSI BACKGROUND COLORS
BG_BLACK = \033[40m
BG_RED = \033[41m
BG_GREEN = \033[42m
BG_YELLOW = \033[43m
BG_BLUE = \033[44m
BG_MAGENTA = \033[45m
BG_CYAN = \033[46m
BG_WHITE = \033[47m

#	STYLES
BOLD = \033[1m
DIM = \033[2m
ITALIC = \033[3m
UNDERLINE = \033[4m
BLINK = \033[5m
REVERSE = \033[7m
HIDDEN = \033[8m

RESET = \033[0m
##################

NAME = libmaths2.a

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes

VERBOSE = 0

ifeq ($(VERBOSE),1)
    SILENT =
else
    SILENT = @
endif

ifeq ($(VERBOSE),1)
    DUMP_OUT =
else
    DUMP_OUT = > /dev/null 2>&1
endif


SRC_FILES = \
	geometry/2D/geometry_overlapping.c \
	geometry/2D/point_overlapping.c \
	geometry/2D/rays2_basics.c \
	geometry/3D/geometry_overlapping.c \
	geometry/3D/plane_utils.c \
	geometry/3D/point_overlapping.c \
	geometry/3D/rays3_basics.c \
	geometry/3D/rays3_intersects.c \
	geometry/geometry_misc.c \
	operations/clamp.c \
	operations/max.c \
	operations/min.c \
	operations/misc_operations.c \
	operations/normalize.c \
	operations/sign.c \
	rng/rng_generation.c \
	rng/rng_init.c \
	rng/rng_utils.c \
	vectors/vec2_base.c \
	vectors/vec2_properties.c \
	vectors/vec3_base.c \
	vectors/vec3_properties.c \
	vectors/vectors_utils.c \
	vectors/vec2_misc.c \
	vectors/vec3_misc.c \
	angles.c \
	sqrt.c \
	easing/easing_quad.c \
	easing/easing_cubic.c \
	easing/easing_back.c \
	easing/blending.c \
	easing/easing_bounce.c

SRC = $(patsubst %.c, $(SRC_DIR)/%.c, $(SRC_FILES))
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
DEP = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.d, $(SRC))

CC = cc 
CFLAGS = -Wall -Werror -Wextra -O3 -Winline
INCLUDES = -I$(INC_DIR)

$(NAME): $(OBJ)
	$(SILENT) $(AR) rcs $@ $^ $(DUMP_OUT)
	@echo "$(BG_GREEN)>>> Library $@ built$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile | $(OBJ_DIR)
	$(SILENT) mkdir -p $(dir $@)
	@echo "$(BLUE)>>> Compiling $<...$(RESET)"
	$(SILENT)$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@echo "$(YELLOW)>>> Directory '$(OBJ_DIR)' created!$(RESET)"
	$(SILENT)mkdir -p $(OBJ_DIR)

clean:
	@echo "$(YELLOW)>>> Cleaning objects$(RESET)"
	rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(YELLOW)>>> Cleaning all$(RESET)"
	rm -f $(NAME)

re: fclean all

-include $(DEP)

.PHONY: all cleanlibs clean fclean re debug debug_env debug_trueclean