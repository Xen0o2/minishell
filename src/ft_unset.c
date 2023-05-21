/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:37:59 by alecoutr          #+#    #+#             */
/*   Updated: 2023/05/21 11:57:49 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_find_index(char *arg)
{
	int		index;
	char	**values;

	index = -1;
	while (g_lobal->env[++index])
	{
		values = better_split(g_lobal->env[index], &equal_split);
		if (ft_strcmp(values[0], arg) == 0)
			return (free_tab(values), index);
		free_tab(values);
	}
	return (-1);
}

void	remove_env(int index)
{
	char	**tmp;
	int		length;
	int		i;
	
	tmp = ft_strrdup(g_lobal->env);
	length = ft_strrlen(g_lobal->env);
	free_tab(g_lobal->env);
	g_lobal->env = malloc(sizeof(char *) * (length));
	length = -1;
	i = 0;
	while (tmp[++length])
		if (length != index)
			g_lobal->env[i++] = ft_strdup(tmp[length]);
	g_lobal->env[i] = NULL;
	free_tab(tmp);
}

void	ft_unset(char **args)
{
	int	i;
	int	index;

	i = 0;
	while (args[++i])
	{
		index = unset_find_index(args[i]);
		if (index != -1)
			remove_env(index);
	}
}

void	print_env()
{
	int	i;

	i = -1;
	printf("--- OK ---\n");
	while (g_lobal->env[++i])
		printf("%s\n", g_lobal->env[i]);
	printf("--- KO ---\n");
}