/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:00:55 by mdoumi            #+#    #+#             */
/*   Updated: 2023/03/20 14:25:45 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signalhandler(int sig)
{
	int	id;

	id = waitpid(-1, NULL, WNOHANG);
	if (id < 0)
	{
		g_vars->last_status = 1;
		if (sig == SIGINT)
		{
			if (g_vars->newline == 1)
			{
				write(1, "\n", 1);
				rl_on_new_line();
				rl_replace_line("", 0);
				rl_redisplay();
			}
			g_vars->newline = 1;
		}
	}
	if (sig == SIGQUIT)
	{
	}
}
