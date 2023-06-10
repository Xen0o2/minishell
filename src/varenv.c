/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:53:59 by ^@^ Foxan ^       #+#    #+#             */
/*   Updated: 2023/03/22 17:30:15 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_s(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	if (str)
		free(str);
}

char	*ft_getenv(char *name)
{
	int		i;
	char	**str;
	char	*c;

	i = 0;
	if (name)
	{
		while (g_vars->env[i])
		{
			str = ft_split(g_vars->env[i], '=');
			if (ft_strcmp(str[0], name) == 0)
			{
				c = build_value(str);
				free_s(str);
				return (c);
			}
			free_s(str);
			i++;
		}
		return (NULL);
	}
	return (NULL);
}

char	*build_value(char **str)
{
	int		i;
	char	*res;

	i = 1;
	res = ft_strdup(str[1]);
	if (str[2])
		res = ft_strjoinnfree(&res, &str[2], "=");
	return (res);
}
