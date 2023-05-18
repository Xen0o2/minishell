/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:48:24 by alecoutr          #+#    #+#             */
/*   Updated: 2023/05/18 15:51:17 by alecoutr         ###   ########.fr       */
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

char	**sort_env(void)
{
	char	**copy;
	int		i;
	int		times;
	int		length;
	int		move;

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

void	export_without_args(void)
{
	int		i;
	char	**sorted_env;
	char	**env;

	i = -1;
	sorted_env = sort_env();
	while (sorted_env[++i])
	{
		env = better_split(sorted_env[i], &export_split);
		if (env[1])
			printf("declare -x %s=\"%s\"\n", env[0], env[1]);
		else
			printf("declare -x %s\n", env[0]);
		free_tab(env);
	}
	free_tab(sorted_env);
}

int	realloc_env(void)
{
	char	**tmp;
	int		length;

	tmp = ft_strrdup(g_lobal->env);
	length = ft_strrlen(g_lobal->env);
	free_tab(g_lobal->env);
	g_lobal->env = malloc(sizeof(char *) * (length + 1));
	length = -1;
	while (tmp[++length])
		g_lobal->env[length] = ft_strdup(tmp[length]);
	free_tab(tmp);
	return (length);
}

void	ft_export(char **args)
{
	int	i;
	int	length;

	length = ft_strrlen(args);
	if (length == 0)
		export_without_args();
	else
	{
		i = -1;
		while (args[++i])
			if (is_valid_arg(args[i]))
				add_arg(args[i]);
	}
}
