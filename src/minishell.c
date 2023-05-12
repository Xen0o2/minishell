/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:28:50 by mdoumi            #+#    #+#             */
/*   Updated: 2023/05/12 16:57:48 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_line(char *str)
{
	
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;

	char *line;
	int	run;

	run = 1;
	while (run)
	{
		if (line)
			free(line);
		line = readline("minishell ");
		if (check_line(line))
		{
			printf("Lets go\n");
		}

	}
}
