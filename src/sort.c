/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:32:48 by mdoumi            #+#    #+#             */
/*   Updated: 2023/03/23 08:42:02 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sswap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	ft_strrlen(char **strr)
{
	int	i;

	i = 0;
	while (strr && strr[i])
		i++;
	return (i);
}

char	**ft_strrcpy(char **strr)
{
	int		i;
	char	**copie;

	i = 0;
	copie = malloc(sizeof(char *) * (ft_strrlen(strr) + 1));
	while (strr[i])
	{
		copie[i] = ft_strdup(strr[i]);
		i++;
	}
	copie[i] = NULL;
	return (copie);
}

char	**ft_strrcpyy(char **strr)
{
	int		i;
	char	**copie;

	i = 0;
	copie = malloc(sizeof(char *) * (ft_strrlen(strr) + 2));
	while (strr[i])
	{
		copie[i] = ft_strdup(strr[i]);
		i++;
	}
	copie[i] = NULL;
	copie[i + 1] = NULL;
	free_s(strr);
	return (copie);
}

char	**sorted_env(void)
{
	int		i;
	int		j;
	char	**sorted;

	j = 0;
	sorted = ft_strrcpy(g_vars->env);
	while (j < ft_strrlen(sorted) - 1)
	{
		i = 0;
		while (i < ft_strrlen(sorted) - 1)
		{
			if (ft_strcmp(sorted[i], sorted[i + 1]) > 0)
				ft_sswap(&sorted[i], &sorted[i + 1]);
			i++;
		}
		j++;
	}
	return (sorted);
}
