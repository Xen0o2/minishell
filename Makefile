# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/12 16:31:17 by mdoumi            #+#    #+#              #
#    Updated: 2023/05/13 17:46:22 by alecoutr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = src/minishell.c \
	   src/export.c \
	   src/ft_split.c \
	   src/ft_strlen.c 
OBJS = $(SRCS:.c=.o)

CC = gcc
INC = -I ./include
FLAGS = -Wall -Wextra -Werror -g -g3

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
