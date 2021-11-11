# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/07 18:01:15 by dpavon-g          #+#    #+#              #
#    Updated: 2021/10/21 17:58:19 by dpavon-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = philo

SRCS = 	philo.c\

OBJECTS = $(SRCS:.c=.o) 
LIB_PATH = libft/
LIB_NAME = $(LIB_PATH)libft.a
INCLUDES = -I. -I$(LIB_PATH)
FSANITIZE = -g3 -fsanitize=address
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)

#COLORS
#RED = \033[0;31m
#GREEN = \033[0;32m
#YELLOW = \033[0;33m
#GREY = \033[2;37m
#MAGENTA = \033[0;35m
#CURSIVE = \033[3m
#NO_COLOR = \033[0m

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -s -C $(LIB_PATH)
	@$(CC) $(CFLAGS) $(LINK) $^ -L ./libft/ -l ft -o $@
	@echo "Minishell compiled $(GREEN) ✔✔✔"

clean:
	@rm -f $(OBJECTS)
	@$(MAKE) clean -C libft
	@clear
	@echo "**** Object files removed ****"

normi:
	norminette $(SRCS)

fclean: clean
	@rm -f $(NAME)
	@rm -f libft/libft.a
	@echo "**** Fclean done ****"

re: fclean all

.PHONY:	all debug clean fclean re

.SILENT: $(OBJS)
