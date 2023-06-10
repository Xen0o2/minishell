/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ^@^ Foxan ^@^ <thibaut.unsinger@gmail.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:49:33 by ^@^ Foxan ^@^     #+#    #+#             */
/*   Updated: 2023/03/02 10:49:34 by ^@^ Foxan ^@^    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	load_history(void)
{
	int		fd;
	char	*line;
	char	*linenonl;

	fd = g_vars->history_fd;
	if (fd > 0)
	{
		line = get_next_line(fd);
		while (line)
		{
			linenonl = ft_strdupnonl(line);
			if (linenonl[0] != '\0' && linenonl[0] != '\n')
				add_history(linenonl);
			free(line);
			free(linenonl);
			line = get_next_line(fd);
		}
	}
}

void	store_in_history(char *line)
{
	int	fd;

	add_history(line);
	fd = g_vars->history_fd;
	if (fd > 0)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
}

int	init_history(void)
{
	g_vars->history_fd = open(HISTORY_PATH, O_RDWR | O_APPEND
			| O_CREAT, S_IRWXU);
	if (g_vars->history_fd < 0)
		printf("Error loading history\n");
	return (g_vars->history_fd);
}
