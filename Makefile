# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/20 18:02:23 by pkorsako          #+#    #+#              #
#    Updated: 2024/02/22 17:57:20 by pkorsako         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

########### V A R I A B L E S #############

NAME		= cub3d
INCLUDES	= -Iincludes -Ilibft
LIBFT		= -Llibft -lft
SRC_DIR		= srcs
OBJ_DIR		= obj
CC			= cc
CFLAGS		= -g -Wall -Wextra -Werror

############### S O U R C E S #############

SRC_FILES	:= $(shell find $(SRC_DIR) -type f -name "*.c")
SRCS		:= $(SRC_FILES)
OBJS		:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

################ R U L E S ################

all				: $(NAME)

$(NAME)			: $(OBJS)
	make -s -C libft/
	$(CC) $(OBJS) $(CFLAGS) $(INCLUDES) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o	: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean			:
	$(MAKE) clean -s -C libft/
	$(RM) -r $(OBJ_DIR)

fclean			: clean
	$(MAKE) fclean -s -C libft/
	$(RM) -r $(NAME)
	
re				: fclean all
