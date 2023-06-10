/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:04:52 by mdoumi            #+#    #+#             */
/*   Updated: 2023/04/13 16:09:00 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	afficher_commande(t_cp *cmd)
{
	char	*buff;

	buff = ft_strdup("");
	while (cmd)
	{
		buff = ft_strjoinnfree(&buff, cmd->fields, " ");
		cmd = cmd->next;
	}
	printf("%s\n", buff);
}

void	ft_gauche(t_cp *cdm)
{
	int		fd;
	t_cp	*haha;

	fd = open(cdm->next->command, O_RDONLY, 0777);
	if (fd < 0)
		return (perror(strerror(errno)));
	dup2(fd, STDIN_FILENO);
	close(fd);
	haha = la_commande_sans_la_fleche(cdm);
	if (haha)
		execute(haha);
}

//void	ft_gauche(t_cp *cmd_line)
//{
	//int		fd;
	//t_cp	*haha;

	//haha = cmd_line->next;
	//while (haha && haha->fields[ft_strrlen(haha->fields) - 1][0] == '<')
	//{
		//fd = open(haha->command, O_RDONLY, 0777);
		//if (fd < 0)
			//return (perror(strerror(errno)), (void)close(fd));
		//haha = haha->next;
	//}
	//fd = open(haha->command, O_RDONLY, 0777);
	//if (fd < 0)
		//return (perror(strerror(errno)), (void)close(fd));
	//dup2(fd, STDIN_FILENO);
	//if (!is_sep(cmd_line->command))
		//haha = gauche_skip(cmd_line);
	//if (!is_sep(cmd_line->command))
		//execute(haha);
	//if (!is_sep(cmd_line->command))
		//free_commands(haha);
	//dup2(g_vars->instd, STDIN_FILENO);
	//close(fd);
//}

void	ft_extreme_gauche(t_cp *cmd_line)
{
	int		here_exit;
	int		fd;
	int		cpy;
	char	*line;

	here_exit = 0;
	fd = open(".here_doc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		return (perror(strerror(errno)));
	while (!here_exit)
	{
		cpy = dup(1);
		dup2(g_vars->outstd, STDOUT_FILENO);
		line = readline(" <$ llehsinim ☺ ");
		dup2(cpy, STDOUT_FILENO);
		if (line && *line)
		{
			if (ft_strcmp(cmd_line->next->command, line) == 0)
				here_exit = 1;
			else
				(write(fd, line, ft_strlen(line)), write(fd, "\n", 1));
			free(line);
		}
	}
	ft_extreme_gauche_2(cmd_line);
}

void	ft_extreme_gauche_2(t_cp *cdm)
{
	int		fd;
	t_cp	*haha;

	fd = open(".here_doc", O_RDONLY, 0777);
	if (fd < 0)
		return (perror(strerror(errno)));
	dup2(fd, STDIN_FILENO);
	close(fd);
	haha = la_commande_sans_la_fleche(cdm);
	if (haha)
		execute(haha);
}

void	create_file(int fd, t_cp *cdm)
{
	fd = open(cdm->next->command, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	close(fd);
}
