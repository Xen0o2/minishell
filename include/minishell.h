/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:54:44 by ^@^ Foxan ^       #+#    #+#             */
/*   Updated: 2023/06/11 17:44:34 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef HISTORY_PATH
#  define HISTORY_PATH "./.minishell_history"
# endif

# define SIZEOF_CHEVRON_DROITE 256

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include "get_next_line_bonus.h"

typedef struct s_vars
{
	char	**env;
	int		exit;
	int		history_fd;
	int		last_status;
	char	*line;
	int		exit_status;
	int		outstd;
	int		instd;
	int		newline;
}	t_vars;

typedef struct s_command_part
{
	char					*str;
	char					*command;
	char					**fields;
	char					**args;
	struct s_command_part	*next;
}	t_cp;

typedef struct s_line
{
	int		fd[2];
	int		pid1;
	int		pid2;
	t_cp	*haha;
	char	**paths;
	int		i;
	int		r;
	char	*path;
	char	*command_path;
	char	*buff;
}	t_line;

typedef struct s_arguments
{
	t_cp	*tmp;
	int		len;
	char	*buff;
}	t_arguments;

typedef struct s_arguments2
{
	t_cp	*haha;
	int		i;
	char	**bufff;
}	t_arguments2;

typedef struct s_arguments3
{
	int	i;
	int	in_q;
	int	nb_q;
	int	j;
}	t_arguments3;

typedef struct s_arguments4
{
	int		start;
	int		in_q;
	int		end;
	t_cp	*cmds;
	char	*str;
	int		type;
}	t_arguments4;

typedef struct s_ab
{
	int		i;
	int		j;
	char	*c;
}	t_ab;

t_vars	*g_vars;

char	*ft_getenv(char *name);
void	ft_env(void);
char	**ft_splitargs(char const *s, char c);
void	substitute(char **field);
char	*ft_strdup(char *s1);
char	**ft_strrdup(char **s1);
int		ft_strcmp(char *s1, char *s2);
char	**ft_split(char const *s, char c);
void	free_s(char **str);
void	ft_pwd(void);
void	ft_cd(char *path);
t_cp	*la_commande_sans_la_fleche(t_cp *cdm);
void	ft_echo(char **fields);
int		update(char c, int *in_q);
void	ft_unset(char **fields);
char	**sorted_env(void);
char	*ft_enlever_redirection(char *str);
int		ft_strrlen(char **strr);
char	**ft_strrcpy(char **strr);
char	**ft_strrcpyy(char **strr);
void	signalhandler(int sig);
void	*init_gvars(int argc, char **argv, char **env);
void	set_sep(char *sep, char c, const char *s1, int len);
int		is_n(char **field);
int		verif_line(char *line);
int		verify_sep(char *str);
t_cp	*parse_line(char *line);
char	**parse_command(char *command);
t_cp	*parse_commands(t_cp *commands);
void	free_commands(t_cp *commands);
int		is_sep(char *c);
t_cp	*new_part(char *str);
t_cp	*append(t_cp **command, t_cp	*new_part);
int		ft_len(t_cp	*liste);
int		is_alpha(char c);
int		is_alnumscore(char c);
char	*replace_env(char *str, int *i);
char	*find_var(char *str, int *j, int i);
char	*replace_home(char *str, int *i);
char	*replace_status(char *str, int *i);
t_cp	*create_command(char *str, int fre);
t_cp	*compress_args(t_cp *cmd_line);
char	*ft_strdupnonl(char *s1);
char	*ft_strldup(char *s1, int l);
char	*ft_strjoin(char const *s1, char const *s2);
void	execute(t_cp *cmd_line);
void	execute_command(char *command, t_cp *cmd_line);
void	execute_from_path(char *command, char **args);
void	execute_command_from_path(char *command, char **args);
void	ft_gauche(t_cp *cmd_line);
t_cp	*skip_first(t_cp *cmd_line);
t_cp	*gauche_skip(t_cp	*cmd_line);
void	ft_extreme_gauche(t_cp *cmd_line);
int		init_history(void);
void	load_history(void);
void	store_in_history(char *line);
void	ft_pipe(t_cp *cmd_line);
void	gerer_txt(t_cp *cmd_line, int mode);
void	ft_droite(t_cp *cmd_line, int mode);
int		ft_cmp(char *c);
char	*ft_itoa(int n);
char	*ft_strjoinfree(char **s1, char const *s2);
char	*ft_strjoinn(char *s1, char **str2);
char	*ft_strjoinnfree(char **s1, char **str2, char *sep);
void	ft_pipex(t_cp *cmd_line);
void	ft_extreme_gauche_2(t_cp *cmd_line);
void	printe(char *str);
int		end(void);
int		ft_atoi(char *str);
void	exit_(t_cp *cmd_line);
void	trim_quotes(char **field);
void	afficher_commande(t_cp *cmd);
void	reset_args(t_cp *tmp, int len);
void	create_file(int fd, t_cp *cdm);
char	*build_value(char **str);
char	**ft_strrldup(char **s1, int l);
void	space_arrows(char **field);
int		is_simple_sep(char c);
int		is_only_spaces(char *str);
int		is_dsep(int s);
int		next_is_sep(char *str);
void	ft_strswap(char **s1, char **s2);
char	**sort_env(void);
void	export_without_args(void);
int		realloc_env(void);
void	ft_export(char **args);
int		invalid_char_in_arg(char *arg);
int		is_valid_arg(char *arg);
int		equal_split(char c);
void	add_arg(char *arg);
char	**better_split(char const *s, int (*cmp)(char c));

#endif //MINISHELL_H
