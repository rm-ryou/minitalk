# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmoriya <rmoriya@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/03 16:29:25 by rmoriya           #+#    #+#              #
#    Updated: 2022/05/21 10:47:34 by rmoriya          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_SERVER := server
NAME_CLIENT := client
LIBFT := libft.a
INCLUDE := ./include/
LIBFTDIR := ./libft/
CFLAGS := -Wall -Wextra -Werror -MP -MMD
SRCS_DIR := ./srcs/
OBJS_DIR := ./objs/
SRC_SERVER = $(SRCS_DIR)server.c
SRC_CLIENT = $(SRCS_DIR)client.c
OBJ_SERVER = $(addprefix $(OBJS_DIR), $(notdir $(SRC_SERVER:.c=.o)))
OBJ_CLIENT = $(addprefix $(OBJS_DIR), $(notdir $(SRC_CLIENT:.c=.o)))

.PHONY : all
all : $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_CLIENT) : $(OBJ_CLIENT)
	$(MAKE) -C $(LIBFTDIR)
	$(CC) $(CFLAGS) -I $(INCLUDE) $(OBJ_CLIENT) $(LIBFTDIR)libft.a  -I $(INCLUDE) -o $@

$(NAME_SERVER) : $(OBJ_SERVER)
	make -C $(LIBFTDIR)
	$(CC) $(CFLAGS) -I $(INCLUDE) $(OBJ_SERVER) $(LIBFTDIR)libft.a  -I $(INCLUDE) -o $@

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -I $(INCLUDE) $< -c -I $(INCLUDE) -o $@

.PHONY : clean
clean :
	make clean -C $(LIBFTDIR)
	$(RM) -rf $(OBJS_DIR)

.PHONY : fclean
fclean : clean
	make fclean -C $(LIBFTDIR)
	$(RM) $(NAME_CLIENT) $(NAME_SERVER)

.PHONY : re
re : fclean all
