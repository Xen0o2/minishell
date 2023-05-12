#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef HISTORY_PATH
#  define HISTORY_PATH "./.minishell_history"
# endif

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_glo
{
	char	**env;
	int		last_status;
}	t_glo;

t_glo	*global;

char	**ft_strrdup(char **s1);
char	*ft_strdup(char *s1);
char    **ft_split(char *s, char c);
char    *ft_substr(char *s, int start, int len);
int		ft_strlen(char *str);

#endif
