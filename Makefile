# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/20 18:02:23 by pkorsako          #+#    #+#              #
#    Updated: 2024/04/15 20:10:56 by pkorsako         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

########### V A R I A B L E S #############

NAME		= cub3D
NAME_BONUS	= cub3D_bonus
INCLUDES	= -Iincludes -Ilibft
LIBFT		= -Llibft -lft
SRC_DIR		= srcs
SRC_BONUS	= srcs_bonus
OBJ_DIR		= obj
OBJ_BONUS	= obj_bonus
CC			= cc
MLX			= -I mlx -L./mlx -lmlx -lXext -lX11 -lm
LIBS		= -Llibft -lft -Lmlx -lmlx -lXext -lX11 -lm
CFLAGS		= -g -Wall -Wextra -Werror

############### S O U R C E S #############

SRC_FILES		:= $(shell find $(SRC_DIR) -type f -name "*.c")
SRCS			:= $(SRC_FILES)
OBJS			:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

SRCS_BONUS		= $(shell find $(SRC_BONUS) -name "*.c")
OBJS_BONUS		= $(SRCS_BONUS:$(SRC_BONUS)/%.c=$(OBJ_BONUS)/%.o)

################ R U L E S ################

all				: $(NAME)

$(NAME)			: $(OBJS)
	@make -s -C libft/
	@$(CC) $(OBJS) $(MLX) $(CFLAGS) $(INCLUDES) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o	: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_BONUS)/%.o: $(SRC_BONUS)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean			:
	$(MAKE) clean -s -C libft/
	$(RM) -r $(OBJ_DIR)
	$(RM) -r $(OBJ_BONUS)

fclean			: clean
	$(MAKE) fclean -s -C libft/
	$(RM) $(NAME) $(NAME_BONUS)
	
re				: fclean all

bonus			: $(OBJS_BONUS)
	@make -s -C libft/
	@$(CC) $(OBJS_BONUS) $(LIBS) -o $(NAME_BONUS)

re_bonus		: fclean bonus
