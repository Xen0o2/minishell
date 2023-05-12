#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef HISTORY_PATH
#  define HISTORY_PATH "./.minishell_history"
# endif

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_glo
{
	char	**env;
	int		last_status;
}	t_glo;

t_glo	*global;

#endif
