/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 09:35:52 by mdoumi            #+#    #+#             */
/*   Updated: 2023/06/11 18:06:37 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	case1(char ***sorted2);
void	case2(char ***str, char ***s, char ***fie, int *error);

int	export_error(int error, char *str)
{
	if (error == 1)
		printf("bash: export: `%s': not a valid identifier\n", str);
	return (1);
}

int	check_export_args(char **fields)
{
	int		i;
	int		j;
	char	**buff;

	i = 0;
	while (fields[i])
	{
		j = 0;
		buff = ft_split(fields[i], '=');
		if (fields[i][0] == '=' || !buff || !buff[0] || !(is_alpha(buff[0][0])
			|| buff[0][0] == '_'))
			return (free_s(buff), export_error(1, fields[i]));
		while (buff[0][j])
		{
			if (!is_alnumscore(buff[0][j]))
				return (free_s(buff), export_error(1, fields[i]));
			j++;
		}
		free_s(buff);
		i++;
	}
	return (0);
}

void	ft_export(char **fields)
{
	char	**str;
	char	**sorted;
	char	**splited;
	int		error;

	error = 0;
	sorted = sorted_env();
	if (fields[0][0] == ' ')
		case1(&sorted);
	else
		case2(&str, &splited, &fields, &error);
	free_s(sorted);
	g_vars->last_status = error;
}

void	case1(char ***sorted2)
{
	char	**sorted;
	char	**splited;
	int		i;

	i = 0;
	sorted = *sorted2;
	while (sorted[i])
	{
		splited = ft_split(sorted[i], '=');
		if (splited[1])
			printf("declare -x %s=\"%s\"\n", splited[0], splited[1]);
		else
			printf("declare -x %s\n", splited[0]);
		free_s(splited);
		i++;
	}
}

void	case2(char ***str, char ***s, char ***fie, int *error)
{
	t_ab	y;

	y.i = -1;
	if (check_export_args(*fie) == 1)
		return ((void)(*error = 1));
	while ((*fie)[++y.i])
	{
		((void)0, *s = ft_split((*fie)[y.i], '='), y.c = ft_getenv((*s)[0]));
		if (y.c != NULL)
		{
			y.j = -1;
			while (g_vars->env[++y.j])
			{
				*str = ft_split(g_vars->env[y.j], '=');
				if (ft_strcmp((*str)[0], (*s)[0]) == 0)
					(free(g_vars->env[y.j]),
						g_vars->env[y.j] = ft_strdup((*fie)[y.i]));
				free_s(*str);
			}
		}
		if (y.c == NULL)
			((void)0, g_vars->env = ft_strrcpyy(g_vars->env),
				g_vars->env[ft_strrlen(g_vars->env)] = ft_strdup((*fie)[y.i]));
		(free_s((*s)), free(y.c));
	}
}
