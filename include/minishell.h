/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:26:16 by mdoumi            #+#    #+#             */
/*   Updated: 2023/05/18 15:51:06 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef HISTORY_PATH
#  define HISTORY_PATH "./.minishell_history"
# endif

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>

# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_glo
{
	char	**env;
	int		last_status;
}	t_glo;

t_glo	*g_lobal;

typedef struct s_split
{
	char	**tab;
	int		i;
	int		j;
	int		sep;
	int		length;
}	t_split;

typedef struct s_line
{
	char	*raw;
	char	*raw_sans_sep;

	char	*command;
	char	**args;
	char	**fields;

	char	*sep;
}	t_line;

//better_split.c
char	**better_split(char const *s, int (*cmp)(char c));

//builtin.c
void	ft_exit(void);
void	ft_env(void);
void	ft_pwd(void);
void	ft_cd(char *path);
void	ft_export(char **args);


//ft_export.c
void	ft_strswap(char **s1, char **s2);
char	**sort_env(void);
void	export_without_args(void);
int		realloc_env(void);

//export_args.c
int		invalid_char_in_arg(char *arg);
int		is_valid_arg(char *arg);
int		export_split(char c);
void	add_arg(char *arg);

//ft_strdup.c
char	*ft_strdup(char *s1);
char	**ft_strrdup(char **s1);

//ft_strlen.c
int		ft_strlen(char *str);
int		ft_strrlen(char **strr);

//ft_substr.c
char	*ft_substr(char *s, int start, int len);

//minishell.c
int		is_white(char c);
int		check_line(char *str);
void	ft_exit(void);
int		ft_strcmp(char *s1, char *s2);
char	*ft_lower(char *str);
void	launch_command(char *str);
void	init_global(char **env);

//parsing.c
void	afficher_tab(t_line **tab);
void	afficher_line(t_line *line);
t_line	*fill_line(char *str, int *i, int *j);
int		ft_cleanlen(char *str);
t_line	**parse_line(char *str);

//utils.c

int		is_white(char c);
int		is_sep(char c);

char	**ft_strrdup(char **s1);
char	*ft_strdup(char *s1);
char    **ft_split(char *s, char c);
char    *ft_substr(char *s, int start, int len);
int		ft_strlen(char *str);
int		ft_strrlen(char **str);
int 	ft_strcmp(char *s1, char *s2);
int		ft_strrlen(char **strr);
void	free_tab(char **tab);

#endif
