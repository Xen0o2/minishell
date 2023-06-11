/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:10:05 by ^@^ Foxan ^       #+#    #+#             */
/*   Updated: 2023/06/11 17:58:34 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_cp *cmd_line)
{
	if (ft_len(cmd_line) == 1)
		execute_command(cmd_line->command, cmd_line);
	else if (ft_len(cmd_line) > 0)
		ft_pipe(cmd_line);
	g_vars->newline = 1;
}

void	execute_command(char *command, t_cp *cmd_line)
{
	if (!command)
		return (printe("Commande non trouvee UwU\n"));
	if (!ft_strcmp(command, "pwd") || !ft_strcmp(command, "PWD"))
		ft_pwd();
	else if (!ft_strcmp(command, "cd") || !ft_strcmp(command, "CD"))
		ft_cd(cmd_line->args[0]);
	else if (!ft_strcmp(command, "echo") || !ft_strcmp(command, "ECHO"))
		ft_echo(cmd_line->args);
	else if (!ft_strcmp(command, "env") || !ft_strcmp(command, "ENV"))
		ft_env();
	else if (!ft_strcmp(command, "exit") || !ft_strcmp(command, "EXIT"))
		exit_(cmd_line);
	else if (!ft_strcmp(command, "export") || !ft_strcmp(command, "EXPORT"))
		ft_export(cmd_line->args);
	else if (!ft_strcmp(command, "unset") || !ft_strcmp(command, "UNSET"))
		ft_unset(cmd_line->args);
	else
		execute_from_path(command, cmd_line->fields);
}

void	execute_from_path(char *command, char **args)
{
	int		r;
	int		status;

	r = fork();
	if (r == 0)
	{
		r = execve(command, args, g_vars->env);
		execute_command_from_path(command, args);
	}
	if (r > 0)
		waitpid(r, &status, WIFEXITED(r));
	g_vars->last_status = WEXITSTATUS(status);
}

void	execute_command_from_path(char *command, char **args)
{
	t_line	a;

	a.buff = ft_getenv("PATH");
	if (!a.buff)
		(printe("Commande non trouvee UwU\n"), exit(127));
	a.paths = ft_split(a.buff, ':');
	free(a.buff);
	a.i = -1;
	a.r = -1;
	while (a.paths[++a.i] && a.r == -1)
	{
		a.path = ft_strjoin(a.paths[a.i], "/");
		a.command_path = ft_strjoin(a.path, command);
		free(a.path);
		a.r = execve(a.command_path, args, g_vars->env);
		free(a.command_path);
	}
	if (a.paths[a.i])
		free_s(a.paths);
	else
		printe("Commande non trouvee UwU\n");
	if (a.paths[a.i])
		exit(errno);
	else
		exit(127);
}

int	ft_len(t_cp	*liste)
{
	t_cp	*tmp;
	int		len;

	tmp = liste;
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}
