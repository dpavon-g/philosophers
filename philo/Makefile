# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/07 18:01:15 by dpavon-g          #+#    #+#              #
#    Updated: 2022/02/07 18:49:22 by dpavon-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc -pthread
INCLUDES = -I.
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

SRCS =	src/philo.c\
		src/philo_aux.c\
		src/philo_aux_2.c\
		src/philo_utils.c\
		
OBJECTS = $(SRCS:.c=.o) 

all: $(NAME)


$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "$(GREY) Philosophers compiled $(GREEN) ✔✔✔"

clean:
	@rm -f $(OBJECTS)
	@clear
	@echo "$(RED) **** Object files removed **** $(NO_COLOR)"

normi:
	norminette $(SRCS)

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED) **** Fclean done **** $(NO_COLOR)"

re: fclean all

.PHONY:	all debug clean fclean re

.SILENT: $(OBJS)
