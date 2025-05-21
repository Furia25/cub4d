.PHONY: all clean fclean re libft

# ------ COLORS ------ #

_END			= \033[0m
_GREY			= \033[0;30m
_RED			= \033[0;31m
_GREEN			= \033[0;32m
_YELLOW			= \033[0;33m
_BLUE			= \033[0;34m
_PURPLE			= \033[0;35m
_CYAN			= \033[0;36m
_BOLD			= \e[1m

# ------ VARIABLES ------ #

NAME			= cub3d
CC				= cc
CFLAGS			= -Wall -Wextra -Werror
LFLAGS 			= -L$(P_MLX) -L$(P_INC) -lmlx -lXext -lX11 -lm -lbsd

# ------ PATHS ------ #

P_OBJ 			= obj/
P_SRC 			= src/
P_UTILS			= $(P_SRC)utils/
P_INC			= includes/
P_LIB			= libft/
P_MLX			= mlx/

# ------ FILES ------ #

MAIN			= main			init_game		\
				end_game		keys_utils		\
				map_utils

UTILS			= 

HDR_SRC			= libft			mlx_int			\
				mlx				cub3d

SRC_MAIN		= $(addprefix $(P_SRC), $(addsuffix .c, $(MAIN)))
SRC_UTILS		= $(addprefix $(P_UTILS), $(addsuffix .c, $(UTILS)))
SRC_ALL			= $(SRC_MAIN) $(SRC_UTILS)

OBJ_MAIN 		= $(addprefix $(P_OBJ), $(addsuffix .o, $(MAIN)))
OBJ_UTILS 		= $(addprefix $(P_OBJ), $(addsuffix .o, $(UTILS)))
OBJ_ALL 		= $(OBJ_MAIN) $(OBJ_UTILS)

HEADERS			= $(addprefix $(P_INC), $(addsuffix .h, $(HDR_SRC)))
LIBFT			= $(P_LIB)libft.a
MLX				= $(P_MLX)libmlx_Linux.a		$(P_MLX)libmlx.a

# ------ RULES ------ #

all: 			libft make_mlx $(NAME)

$(NAME):		$(OBJ_ALL) Makefile $(HEADERS) $(LIBFT)
				@$(CC) $(CFLAGS) $(LFLAGS) -I $(P_INC) $(OBJ_ALL) $(LIBFT) $(MLX) -o $@
				@echo "$(_GREEN)$(_BOLD)=> $(NAME) compiled!$(_END)"

$(P_OBJ):
				@mkdir -p $(P_OBJ)

$(P_OBJ)%.o:	$(P_SRC)%.c Makefile $(HEADERS) $(LIBFT) | $(P_OBJ)
				@echo "$(_YELLOW)Compiling $<...$(_END)"
				@$(CC) $(CFLAGS) -I $(P_INC) -c $< -o $@

# $(P_OBJ)%.o:	$(P_UTILS)%.c Makefile $(HEADERS) $(LIBFT) $(MLX) | $(P_OBJ)
# 				@echo "$(_YELLOW)Compiling $<...$(_END)"
# 				@$(CC) $(CFLAGS) -I $(P_INC) -c $< -o $@

libft:		
				@$(MAKE) -C $(P_LIB) --no-print-directory

make_mlx:		
				@$(MAKE) -C $(P_MLX)

# ------ BASIC RULES ------ #

clean: 
				@rm -rf $(P_OBJ)
				@$(MAKE) -C $(P_LIB) clean --no-print-directory
				@$(MAKE) -C $(P_MLX) clean --no-print-directory
				@echo "$(_CYAN)$(NAME) cleaned!$(_END)"

fclean:
				@$(MAKE) clean --no-print-directory
				@$(MAKE) -C $(P_LIB) fclean --no-print-directory
				@rm -rf $(LIBFT)
				@rm -rf $(NAME)
				@echo "$(_CYAN)$(NAME) full cleaned!$(_END)"

re:
				@$(MAKE) fclean --no-print-directory
				@$(MAKE) all --no-print-directory
