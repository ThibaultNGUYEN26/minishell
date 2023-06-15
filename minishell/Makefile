# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/15 17:51:35 by thibnguy          #+#    #+#              #
#    Updated: 2023/06/15 18:12:37 by thibnguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
SOURCES		=	./src
OBJECTS		=	./bin
INCLUDES	=	./includes

SRCS		=	libft/ft_putchar.c \
				libft/ft_putnbr_base.c \
				libft/ft_putstr.c \
				libft/ft_strlen.c \
				printf/ft_nblen.c \
				printf/ft_printf.c

OBJS		=	$(addprefix ${OBJECTS}/, $(SRCS:.c=.o))

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
CINCLUDES	=	-I ${INCLUDES}

BLACK		=	"\033[1;30m"
RED			=	"\033[1;31m"
GREEN		=	"\033[1;32m"
CYAN		=	"\033[1;35m"
BLUE		=	"\033[1;36m"
WHITE		=	"\033[1;37m"
EOC			=	"\033[0;0m"

${OBJECTS}/%.o: ${SOURCES}/%.c
	@mkdir -p $(dir $@)
	@echo $(WHITE)"● Compilation de "$(BLUE)"${notdir $<}"$(EOC)"."
	@${CC} ${CFLAGS} -o $@ -c $< ${CINCLUDES}

all: ${NAME}

${NAME}: ${OBJS} ${OBJECTS}/${NAME}.o
	@echo $(GREEN)"● Compilation du ${NAME}..."$(EOC)
	@${CC} ${CFLAGS} -fsanitize=address -g ${CINCLUDES} -o ${NAME} ${OBJS} ${OBJECTS}/${NAME}.o

clean:
	@echo ${RED}"● Supression des fichiers binaires (.o)..."$(EOC)
	@rm -rf ${OBJECTS}

fclean: clean
	@echo ${RED}"● Supression des executables et librairies..."$(EOC)
	@rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re