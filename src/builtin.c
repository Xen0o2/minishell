/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:19:27 by mdoumi            #+#    #+#             */
/*   Updated: 2023/03/23 08:57:44 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(void)
{
	int	i;

	i = 0;
	while (g_vars->env[i])
	{
		printf("%s\n", g_vars->env[i]);
		i++;
	}
}

void	degage(int j)
{
	free(g_vars->env[j]);
	while (g_vars->env[j + 1])
	{
		g_vars->env[j] = g_vars->env[j + 1];
		j++;
	}
	g_vars->env[j] = NULL;
	free(g_vars->env[j + 1]);
}

void	ft_unset(char **fields)
{
	int		i;
	int		j;
	char	**splited;

	i = -1;
	if (fields[0][0] == ' ')
		return ;
	if (check_export_args(fields) == 1)
		return ;
	while (fields[++i])
	{
		j = -1;
		while (g_vars->env[++j])
		{
			splited = ft_split(g_vars->env[j], '=');
			if (ft_strcmp(splited[0], fields[i]) == 0)
			{
				(degage(j), free_s(splited));
				break ;
			}
			free_s(splited);
		}
	}
	g_vars->last_status = 0;
}

void	exit_(t_cp *cmd_line)
{
	int	code;
	int	i;

	i = (cmd_line->args[0][0] == '-') - 1;
	while (cmd_line->args[0][0] != ' ' && cmd_line->args[++i])
	{
		if (!('0' <= cmd_line->args[0][i] && cmd_line->args[0][i] <= '9')
			|| cmd_line->args[1])
			return ((void) printf("Error\n"));
	}
	code = ft_atoi(cmd_line->args[0]);
	g_vars->exit = 1;
	g_vars->exit_status = code;
}
