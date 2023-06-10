/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 09:00:38 by mdoumi            #+#    #+#             */
/*   Updated: 2023/04/13 15:22:52 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cp	*create_command(char *str, int fre)
{
	t_cp	*cmd_line;

	cmd_line = parse_line(str);
	parse_commands(cmd_line);
	if (fre == 1)
		free(str);
	else if (fre == 3)
		g_vars->newline = 0;
	return (cmd_line);
}

//Input : echo "uwu" | grep a | grep b | grep c
//Output : echo "uwu" | grep b | grep c
t_cp	*compress_args(t_cp *cmd_line)
{
	char	*buff;
	t_cp	*bgn;

	buff = ft_strjoinn(cmd_line->command, cmd_line->args);
	bgn = cmd_line->next;
	while (bgn->next)
	{
		buff = ft_strjoinfree(&buff, bgn->fields[ft_strrlen(bgn->fields) - 1]);
		buff = ft_strjoinfree(&buff, " ");
		buff = ft_strjoinfree(&buff, bgn->next->command);
		buff = ft_strjoinnfree(&buff, bgn->next->args, " ");
		buff = ft_strjoinfree(&buff, " ");
		bgn = bgn->next;
	}
	bgn = create_command(buff, 1);
	return (bgn);
}

t_cp	*skip_first(t_cp *cmd_line)
{
	char	*buff;
	t_cp	*n;

	n = cmd_line->next;
	buff = ft_strdup("");
	buff = ft_strjoinnfree(&buff, n->args, " ");
	if (ft_strrlen(n->fields) > 2)
	{
		buff = ft_strjoinfree(&buff, " ");
		buff = ft_strjoinfree(&buff, n->fields[ft_strrlen(n->fields) - 1]);
	}
	n = n->next;
	while (n)
	{
		buff = ft_strjoinnfree(&buff, n->fields, " ");
		n = n->next;
	}
	n = create_command(buff, 1);
	return (n);
}

t_cp	*gauche_skip(t_cp	*cmd_line)
{
	char	*buff;
	t_cp	*bgn;

	bgn = cmd_line;
	buff = ft_strjoin("", bgn->command);
	buff = ft_strjoinfree(&buff, " ");
	buff = ft_strjoinnfree(&buff, bgn->args, " ");
	bgn = create_command(buff, 1);
	return (bgn);
}
