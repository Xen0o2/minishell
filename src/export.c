/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:48:24 by alecoutr          #+#    #+#             */
/*   Updated: 2023/06/10 15:37:53 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strswap(char **s1, char **s2)
{
	char	*copy;
	
	copy = *s1;
	*s1 = *s2;
	*s2 = copy;
}

char	**sort_env()
{
	char	**copy;
    int 	i;
    int 	times;
    int 	length;
    int 	move;

    times = 0;
    move = 1;
    copy = ft_strrdup(g_lobal->env);
    length = ft_strrlen(copy);
    while (move)
    {
        move = 0;
		i = -1;
        while (++i < length - times - 1)
        {
            if (ft_strcmp(copy[i], copy[i + 1]) > 0)
            {
                ft_strswap(&copy[i], &copy[i + 1]);
                move = 1;
            }
        }
		times++;
    }
	return (copy);
}

int export_split(char c)
{
    return (c == '=');
}


void    export_without_args()
{
    int     i;
	int		x;
	char	**sorted_env;
    char    **env;

    i = -1;
	sorted_env = sort_env();
    while (sorted_env[++i])
    {
        env = better_split(sorted_env[i], &export_split);
        free(sorted_env[i]);
        if (env[1])
			printf("declare -x %s=\"%s\"\n", env[0], env[1]);
        else
			printf("declare -x %s\n", env[0]);
		x = -1;
		while (env[++x])
			free(env[x]);
		free(env);
    }
    free(sorted_env);
}

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

int	realloc_env(int i)
{
	char	**tmp;
	int		length;

	tmp = ft_strrdup(g_lobal->env);
	length = ft_strrlen(g_lobal->env);
	free_tab(g_lobal->env);
	g_lobal->env = malloc(sizeof(char *) * (length + i));
	length = -1;
	while (tmp[++length])
		g_lobal->env[length] = ft_strdup(tmp[length]);
	free_tab(tmp);
	return (length);
}

int	invalid_char_in_arg(char *arg)
{
	int		i;
	int		x;
	char	*invalid_char;

	i = -1;
	invalid_char = "$#+-/@.^%!-?.,;:{}[]&";
	while (arg[++i])
	{
		x = -1;
		while (invalid_char[++x])
			if (arg[i] == invalid_char[x])
				return (1);
	}
	return (0);
}

int	check_export_args(char **args)
{
	int		i;
	int		length;
	int		valid_args;

	length = ft_strrlen(args);
	valid_args = 0;
	if (!length)
		return (-1);
	i = -1;
	while (args[++i])
	{
		if (args[i][0] >= '0' || args[i][0] <= '9')
			return (printf("export: `%s': not a valid identifier\n"
			, args[i]), 0);
		if (!invalid_char_in_arg(args[i]))
			return (printf("export: `%s': not a valid identifier\n"
			, args[i]), 0);
		valid_args++;
	}
	return (valid_args);
}
                                                                                                                                                                                                                            
void    export(char **args)
{
    // args = {"ac=salut", "ab"};
    int     valid_args;
    int     length;

    valid_args = check_export_args(args);
    if (valid_args == -1)
        export_without_args();
    else
    {
		length = realloc_env(valid_args);
		valid_args = -1;
        while (args[++valid_args])
            g_lobal->env[length + valid_args] = ft_strdup(args[valid_args]);
    }
}
