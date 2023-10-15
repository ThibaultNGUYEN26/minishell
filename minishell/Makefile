# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/15 17:51:35 by thibnguy          #+#    #+#              #
#    Updated: 2023/10/15 16:33:06 by thibnguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
SOURCES		=	./src
OBJECTS		=	./bin
INCLUDES	=	./includes

SRCS		=	bashvar/ft_bash.c \
				builtins/ft_builtins.c \
				builtins/ft_cd.c \
				builtins/ft_echo.c \
				builtins/ft_env.c \
				builtins/ft_exit.c \
				builtins/ft_export_utils.c \
				builtins/ft_export.c \
				builtins/ft_pwd.c \
				builtins/ft_thibnguy.c \
				builtins/ft_unset.c \
				executor/pipex.c \
				executor/ft_exec_error.c \
				executor/ft_heredoc.c \
				executor/pipex_utils.c \
				executor/redirec_utils.c \
				executor/ft_exec_utils.c \
				get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c \
				lexer/ft_dollar_utils.c \
				lexer/ft_dollar.c \
				lexer/ft_lexer_errors.c \
				lexer/ft_lexer_file_errors.c \
				lexer/ft_lexer.c \
				lexer/ft_quotes.c \
				parser/ft_echo_utils.c \
				parser/ft_parser_echo.c \
				parser/ft_parser_init.c \
				parser/ft_parser_redirec.c \
				parser/ft_parser_utils.c \
				parser/ft_parser.c \
				libft/ft_atoi.c \
				libft/ft_isalnum.c \
				libft/ft_isnumeric.c \
				libft/ft_itoa.c \
				libft/ft_putstr_fd.c \
				libft/ft_putchar_fd.c \
				libft/ft_split.c \
				libft/ft_strchr.c \
				libft/ft_strcmp.c \
				libft/ft_strdup.c \
				libft/ft_strjoin.c \
				libft/ft_strlen.c \
				libft/ft_strncmp.c \
				libft/ft_substr.c \
				signals/ft_signals.c \
				utils/ft_cmds_utils.c \
				utils/ft_stack_utils.c \

OBJS		=	$(addprefix ${OBJECTS}/, $(SRCS:.c=.o))

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g #-fsanitize=address
CINCLUDES	=	-I ${INCLUDES}

BLACK		=	"\033[1;30m"
RED			=	"\033[1;31m"
GREEN		=	"\033[1;32m"
CYAN		=	"\033[1;35m"
BLUE		=	"\033[1;36m"
WHITE		=	"\033[1;37m"
EOC			=	"\033[0;0m"

TOTAL_OBJS := $(words $(OBJS))
COMPILED_OBJS := 0

define print_progress
	printf $(WHITE)"\r● [Compiling]  : "
	$(eval PERCENTAGE=$(shell echo "$(2)*100/$(1)" | bc))
	$(eval FILLED_BLOCKS=$(shell if [ "$(shell echo "$(PERCENTAGE)/10" | bc)" -lt "1" ]; then echo "1"; else echo "$(shell echo "$(PERCENTAGE)/10" | bc)"; fi))
	$(eval EMPTY_BLOCKS=$(shell echo "10 - $(FILLED_BLOCKS)" | bc))
	for i in `seq 1 $(shell echo "$(FILLED_BLOCKS)" | awk '{print int($$1)}')`; do \
		printf $(GREEN)"▇▇▇"; \
	done
	if [ "$(PERCENTAGE)" != "100" ]; then \
		for i in `seq 1 $(EMPTY_BLOCKS)`; do \
			printf $(WHITE)"▇▇▇"; \
		done; \
	fi
	printf $(WHITE)" $(PERCENTAGE)%% $(2) /$(1)files"$(EOC)
endef

${OBJECTS}/%.o: ${SOURCES}/%.c
	@mkdir -p $(dir $@)
	@$(call print_progress, $(TOTAL_OBJS), $(COMPILED_OBJS))
	@$(CC) $(CFLAGS) -o $@ -c $< $(CINCLUDES)
	@$(eval COMPILED_OBJS=$(shell echo "$(COMPILED_OBJS)+1" | bc))

all: ${NAME} norminette

${NAME}: ${OBJS} ${OBJECTS}/${NAME}.o
	@echo $(GREEN)"\n● Compilation of ${NAME}..."$(EOC)
	@${CC} ${CFLAGS}  ${CINCLUDES} -o ${NAME} ${OBJS} ${OBJECTS}/${NAME}.o -lreadline

norminette:
	@norminette | grep "Error!" > /dev/null && echo $(WHITE)"● [Norminette]: "$(RED)"KO\n"$(EOC) || echo $(WHITE)"● [Norminette]: "$(GREEN)"OK\n"$(EOC)

clean:
	@echo ${RED}"● Deletion of binary files (.o)..."$(EOC)
	@rm -rf ${OBJECTS}

fclean: clean
	@echo ${RED}"● Deletion of executables and libraries..."$(EOC)
	@rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re