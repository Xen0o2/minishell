/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:43:05 by ^@^ Foxan ^       #+#    #+#             */
/*   Updated: 2023/04/12 17:10:41 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_sep(char *c)
{
	if (c[0] == '|')
		return (1);
	if (c[0] == '<' && c[1] != '<')
		return (2);
	if (c[0] == '<' && c[1] == '<')
		return (3);
	if (c[0] == '>' && c[1] != '>')
		return (4);
	if (c[0] == '>' && c[1] == '>')
		return (5);
	return (0);
}

t_cp	*new_part(char *str)
{
	t_cp	*part;

	part = malloc(sizeof(t_cp) * 1);
	if (!part)
		return (NULL);
	if (str)
		part->str = str;
	else
		part->str = NULL;
	part->fields = NULL;
	part->args = NULL;
	part->command = NULL;
	part->next = NULL;
	return (part);
}

t_cp	*append(t_cp **command, t_cp *new_part)
{
	t_cp	*tmp;

	if (!*command || !(*command)->str)
	{
		if (*command)
			free_commands(*command);
		*command = new_part;
		return (new_part);
	}
	tmp = *command;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_part;
	return (*command);
}

void	free_commands(t_cp *commands)
{
	t_cp	*tmp;

	if (!commands)
		return ;
	tmp = commands->next;
	while (commands)
	{
		if (commands->command)
			free(commands->command);
		commands->command = NULL;
		if (commands->str)
			free(commands->str);
		commands->str = NULL;
		if (commands->fields)
			free_s(commands->fields);
		commands->fields = NULL;
		if (commands->args)
			free_s(commands->args);
		commands->args = NULL;
		free(commands);
		commands = tmp;
		if (tmp)
			tmp = tmp->next;
	}
	commands = NULL;
}

void	reset_args(t_cp *tmp, int len)
{
	free(tmp->args[len]);
	tmp->args[len] = NULL;
}
