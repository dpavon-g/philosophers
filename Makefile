# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/07 18:01:15 by dpavon-g          #+#    #+#              #
#    Updated: 2021/11/22 15:00:00 by dpavon-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc -pthread
LIB_PATH = libft/
LIB_NAME = $(LIB_PATH)libft.a
INCLUDES = -I. -I$(LIB_PATH)
FSANITIZE = -g3 -fsanitize=address
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)

#COLORS

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
GREY = \033[2;37m
MAGENTA = \033[0;35m
CURSIVE = \033[3m
NO_COLOR = \033[0m

SRCS = philo.c\

OBJECTS = $(SRCS:.c=.o) 

all: $(NAME)


$(NAME): $(OBJECTS)
	@make -s -C $(LIB_PATH)
	@$(CC) $(CFLAGS) $(LINK) $^ -L ./libft/ -l ft -o $@
	@echo "$(GREY) Philosophers compiled $(GREEN) ✔✔✔"

clean:
	@rm -f $(OBJECTS)
	@$(MAKE) clean -C libft
	@clear
	@echo "$(RED) **** Object files removed **** $(NO_COLOR)"

normi:
	norminette $(SRCS)

fclean: clean
	@rm -f $(NAME)
	@rm -f libft/libft.a
	@echo "$(RED) **** Fclean done **** $(NO_COLOR)"

re: fclean all

.PHONY:	all debug clean fclean re

.SILENT: $(OBJS)
