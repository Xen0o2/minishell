# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Foxan         <foxan57@gmail.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 10:23:53 by Foxan             #+#    #+#              #
#    Updated: 2022/11/03 10:23:54 by Foxan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#//= Colors =//#
BOLD			:= \033[1m
BLACK			:= \033[30;1m
RED				:= \033[31;1m
GREEN			:= \033[32;1m
YELLOW			:= \033[33;1m
BLUE			:= \033[34;1m
MAGENTA			:= \033[35;1m
CYAN			:= \033[36;1m
WHITE			:= \033[37;1m
RESET			:= \033[0m

#//= Variables =//#
CC				:= gcc
NAME			:= minishell
PROJECT_NAME	:= MINISHELL
SRCS			:=	./src/main.c \
					./src/varenv.c \
					./src/ft_splitargs.c \
					./src/ft_splitargs_utils.c \
					./src/ft_strdup.c \
					./src/ft_strcmp.c \
					./src/ft_split.c \
					./src/builtin.c \
					./src/builtins2.c \
					./src/sort.c \
					./src/export.c \
					./src/signal.c \
					./src/commands.c \
					./src/ft_strjoin.c \
					./src/parsing.c \
					./src/parsing_utils.c \
					./src/history.c \
					./src/GNL/get_next_line_bonus.c \
					./src/GNL/get_next_line_utils_bonus.c \
					./src/verify.c \
					./src/verify_utils.c \
					./src/replace.c \
					./src/pipe.c \
					./src/pipe_utils.c \
					./src/pipe2.c \
					./src/pipe3.c \
					./src/pipe4.c \
					./src/ft_itoa.c \
					./src/ft_atoi.c

INCLUDES		:= -I ./include
FLAGS			:= -Wall -Wextra -Werror -g -g3
OBJS			:= ${SRCS:.c=.o}
SOMETHING		:= 0
LIBREADLINE		:= -lreadline -L /Users/$$USER/.brew/opt/readline/lib
INCREADLINE		:= -I /Users/$$USER/.brew/opt/readline/include
HISTORY_PATH	:= ./.minishell_history
HISTORY_PATH_C	:= "\"$(HISTORY_PATH)\""

#//= Main compiling rules =//#

all: startall ${NAME} endall

${NAME}: ${OBJS}
	@$(CC) -o $(NAME) $(OBJS) $(LIBREADLINE) $(INCLUDES) $(INCREADLINE)

.c.o:
	@${CC} ${FLAGS} -c $< -o ${<:.c=.o} ${INCLUDES} ${INCREADLINE} -DHISTORY_PATH=${HISTORY_PATH_C} &&  printf "$(MAGENTA)$(PROJECT_NAME)$(RESET)$(BOLD) Compiling: $(notdir $<) \n$(RESET)"
	@$(eval SOMETHING = 1)

#//= Cleaning rules =//#

clean:
	@rm -f ${OBJS} && printf "$(GREEN)Cleaning $(PROJECT_NAME) OBJS...\n$(RESET)"
	@printf "$(YELLOW)Finished cleaning !\n$(RESET)"
	@printf "$(YELLOW)--------------------\n$(RESET)"

fclean: clean cleanhistory # cleaning rule
	@rm -f ${NAME} && printf "$(GREEN)Cleaning $(PROJECT_NAME) $(NAME)...\n$(RESET)"
	@printf "$(YELLOW)Finished cleaning everything !\n$(RESET)"
	@printf "$(YELLOW)--------------------\n$(RESET)"

cleanhistory:
	@rm -f ${HISTORY_PATH} && printf "$(GREEN)Cleaning $(PROJECT_NAME) $(HISTORY_PATH)...\n$(RESET)"
	@printf "$(YELLOW)Finished cleaning !\n$(RESET)"
	@printf "$(YELLOW)--------------------\n$(RESET)"

#//= Beautification rules =//#

startall:
	@printf "$(BOLD)--------------------\n$(RESET)"
	@printf "$(MAGENTA)Starting doing everything\n$(RESET)"
	@printf "$(BOLD)--------------------\n$(RESET)"

endall:
	@if [ $(SOMETHING) = 1 ]; then printf "$(BOLD)Done compiling $(MAGENTA)e$(CYAN)v$(GREEN)e$(YELLOW)r$(BLUE)y$(RED)t$(MAGENTA)h$(CYAN)i$(GREEN)n$(YELLOW)g !\n$(RESET)$(BOLD)--------------------\n$(RESET)$(MAGENTA)Done making $(PROJECT_NAME)!\n$(RESET)"; fi
	@if [ $(SOMETHING) = 0 ]; then printf "$(MAGENTA)Nothing to do !\n$(RESET)"; fi

re:	fclean all

.PHONY: all clean fclean re start end startall endall libdummy
