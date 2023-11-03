# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnualman <tnualman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/03 00:28:11 by tnualman          #+#    #+#              #
#    Updated: 2023/11/03 00:48:12 by tnualman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread
SRCDIR = src
OBJDIR = build
HEADER = src/philo.h
SRC = 	ft_atoi.c \
		philo_main.c \
		philo_utils.c \
		philo_init.c \
		philo_routine.c

OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -I$(HEADER) -o $(NAME)
	@echo "Done!"

$(OBJ): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS)  -c $< -o $@

clean :
	rm -rf $(OBJDIR)
	rm -rf $(NAME).dSYM
	rm -rf .DS_Store

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus
