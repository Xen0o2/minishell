# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/14 19:25:56 by mdoumi            #+#    #+#              #
#    Updated: 2023/05/14 19:36:48 by mdoumi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS =	\
		src/better_split.c \
		src/builtin.c \
		src/ft_strcmp.c \
		src/ft_strdup.c \
		src/ft_strlen.c \
		src/ft_substr.c \
		src/minishell.c \
		src/parsing.c \
		src/utils.c
OBJS = $(SRCS:.c=.o)

CC = gcc
INC = -I ./include
#FLAGS = -Wall -Wextra -Werror -g -g3

LIBREADLINE	= -lreadline -L /Users/$$USER/.brew/opt/readline/lib
INCREADLINE	= -I /Users/$$USER/.brew/opt/readline/include

all: $(NAME)

${NAME}: ${OBJS}
	$(CC) -o $(NAME) $(OBJS) $(LIBREADLINE) $(INC) $(INCREADLINE)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o} ${INC} ${INCREADLINE}

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:	fclean all
