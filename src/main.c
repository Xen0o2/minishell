/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:30:33 by mdoumi            #+#    #+#             */
/*   Updated: 2023/03/23 08:32:06 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_cp	*cmd_line;

	if (!init_gvars(argc, argv, env))
		return (0);
	while (!g_vars->exit)
	{
		if (g_vars->line)
			free(g_vars->line);
		g_vars->line = readline("☺ minishell $> ");
		g_vars->newline = 1;
		g_vars->exit = (g_vars->line == NULL);
		if (g_vars->line && *(g_vars->line) && !is_only_spaces(g_vars->line))
		{
			store_in_history(g_vars->line);
			if (verif_line(g_vars->line))
			{
				cmd_line = create_command(g_vars->line, 3);
				execute(cmd_line);
				free_commands(cmd_line);
			}
			else
				printf("Error\n");
		}
	}
	return (end());
}

void	*init_gvars(int argc, char **argv, char **env)
{
	g_vars = malloc(sizeof(t_vars));
	if (!g_vars)
		return (NULL);
	if (argc > 1)
	{
		printf("Minishell doesn't take args, ssry ! UwU\n");
		free(g_vars);
		exit(1);
	}
	(void) argv;
	g_vars->env = ft_strrdup(env);
	g_vars->line = NULL;
	g_vars->exit = 0;
	g_vars->exit_status = 0;
	g_vars->last_status = 0;
	g_vars->instd = dup(0);
	g_vars->outstd = dup(1);
	g_vars->newline = 1;
	rl_catch_signals = 0;
	init_history();
	load_history();
	signal(SIGINT, signalhandler);
	signal(SIGQUIT, signalhandler);
	return (g_vars);
}

int	end(void)
{
	int	status;

	if (g_vars->exit_status)
		status = g_vars->exit_status;
	else
		status = g_vars->last_status;
	close(g_vars->history_fd);
	free_s(g_vars->env);
	free(g_vars->line);
	free(g_vars);
	printf("K, thx, bye ! UwU\n");
	return (status);
}
