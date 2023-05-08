# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/08 21:52:26 by abrisse           #+#    #+#              #
#    Updated: 2023/05/08 22:05:14 by abrisse          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COLORS
_GREY		=	$'\033[1;30m
_RED		=	$'\033[1;31m
_GREEN		=	$'\033[1;32m
_YELLOW		=	$'\033[1;33m
_BLUE		=	$'\033[1;34m
_PURPLE		=	$'\033[1;35m
_CYAN		=	$'\033[1;36m
_WHITE		=	$'\033[1;37m
_NEUTRAL	=	$'\033[m

# VARIABLE
EXEC	=	cub3d

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -g
IFLAGS	=	-I includes/ -I libs/libft/includes/ -I libs/minilibx-linux/
LDFLAGS	=	-L libs/ -lft -lmlx -lXext -lX11 -lm

INC_PATH=	includes/
DEP_PATH=	deps/
OBJ_PATH=	objs/
LIB_PATH=	libs/
SRC_PATH=	srcs/
vpath %.c $(SRC_PATH)
vpath %.a $(LIB_PATH)
LIB		=	libft/libft.a minilibx-linux/libmlx.a
SRC		=	main.c
DEP		=	$(addprefix $(DEP_PATH), $(SRC:.c=.d))
OBJ		=	$(addprefix $(OBJ_PATH), $(SRC:.c=.o))

# COMPILATION
all		:	$(EXEC)

$(EXEC)	:	$(addprefix $(LIB_PATH), $(LIB)) $(OBJ)
	$(_GREY)$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)$(_NEUTRAL)
	@echo "$(_GREEN)[$(EXEC): Executable created]$(_NEUTRAL)"

%.a		:
	@make -C $(@:.a=) install

$(OBJ_PATH)%.o	:	%.c
	@mkdir -p $(OBJ_PATH) $(DEP_PATH)
	@echo "$(_GREY)Compiling : $<$(_NEUTRAL)"
	@$(CC) -o $@ -c $< $(CFLAGS) $(IFLAGS) -MMD
	@mv $(@:.o=.d) $(DEP_PATH)

-include $(DEP)

# RULES
clean	:
	rm -rf $(OBJ_PATH)
	rm -rf $(DEP_PATH)


fclean	:	clean $(foreach lib, $(LIB, $(LIB_PATH)$(lib:.a=)_fclean)
	rm -rf $(EXEC)
	rm -rf $(addprefix $(LIB_PATH), $(LIB))

%_fclean :
	@make -C $(subst _, , $@)

re		: fclean all

.PHONY	:	all clean fclean re
