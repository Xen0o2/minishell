/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:39:12 by mdoumi            #+#    #+#             */
/*   Updated: 2023/03/22 16:17:44 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//   echo "owo" | grep o | grep a | grep b | grep c

//void	afficher_commande(t_cp *cmd)
//{
	//char	*buff;

	//buff = ft_strdup("");
	//while (cmd)
	//{
		//buff = ft_strjoinn(buff, cmd->fields);
		//cmd = cmd->next;
	//}
	//printf("%s\n", buff);
//}

t_cp	*command_until_npipe(t_cp *cmd_line)
{
	t_cp	*cdm;
	char	*buff;

	cdm = cmd_line;
	buff = ft_strdup("");
	while (cdm && cdm->fields[ft_strrlen(cdm->fields) - 1][0] != '|')
	{
		buff = ft_strjoinnfree(&buff, cdm->fields, " ");
		cdm = cdm->next;
	}
	if (cdm && cdm->fields[ft_strrlen(cdm->fields) - 1][0] == '|')
	{
		buff = ft_strjoinfree(&buff, " ");
		buff = ft_strjoinfree(&buff, cdm->command);
		buff = ft_strjoinnfree(&buff, cdm->args, " ");
	}
	free_commands(cdm);
	cdm = create_command(buff, 1);
	return (cdm);
}

t_cp	*command_apres_npipe(t_cp *cmd_line)
{
	t_cp	*a;

	a = cmd_line;
	while (a->fields[ft_strrlen(a->fields) - 1][0] != '|')
		a = a->next;
	if (a->fields[ft_strrlen(a->fields) - 1][0] == '|')
		a = a->next;
	return (a);
}

void	premiere_partie(int *pid1, int fd[2], t_cp *cmd_line)
{
	t_cp	*haha;

	*pid1 = fork();
	if (*pid1 < 0)
		printf("Error\n");
	if (*pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		haha = command_until_npipe(cmd_line);
		execute(haha);
		free_commands(haha);
		exit(0);
	}
}

void	ft_pipex(t_cp *cmd_line)
{
	t_line	a;

	if (pipe(a.fd) == -1)
		printf("Error\n");
	premiere_partie(&(a.pid1), a.fd, cmd_line);
	dup2(g_vars->outstd, STDOUT_FILENO);
	a.pid2 = fork();
	if (a.pid2 < 0)
		printf("Error\n");
	if (a.pid2 == 0)
	{
		dup2(a.fd[0], STDIN_FILENO);
		close(a.fd[0]);
		close(a.fd[1]);
		a.haha = command_apres_npipe(cmd_line);
		execute(a.haha);
		free_commands(a.haha);
		exit(0);
	}
	dup2(g_vars->instd, STDIN_FILENO);
	close(a.fd[0]);
	close(a.fd[1]);
	waitpid(a.pid1, NULL, 0);
	waitpid(a.pid2, NULL, 0);
	return ;
}
