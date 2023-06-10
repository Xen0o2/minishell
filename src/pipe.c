/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:13:20 by mdoumi            #+#    #+#             */
/*   Updated: 2023/04/13 16:15:24 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Exemple : echo uwu | bonsoir love

str : echo uwu |
command : echo
fields : [echo, uwu, |]
args : [uwu]

->next
str : bonsoir love
command : bonsoir
fields : [bonsoir, love]
args : [love]
*/

void	gerer_txt(t_cp *cmd_line, int mode)
{
	char	*buff;
	t_cp	*bgn;

	bgn = cmd_line;
	buff = ft_strdup("printf \"\"");
	buff = ft_strjoinnfree(&buff, bgn->fields, " ");
	bgn = bgn->next;
	while (bgn)
	{
		buff = ft_strjoinnfree(&buff, bgn->fields, " ");
		bgn = bgn->next;
	}
	bgn = create_command(buff, 1);
	ft_droite(bgn, mode);
}

// Tout ce qu'il reste a faire c'est rajouter echo uwu apres le log.txt
// La gerer_txt il transforme (> log.txt > log2.txt) en
// (printf "" > log.txt > log2.txt)

t_cp	*la_commande_sans_la_fleche(t_cp *cdm)
{
	char	*buff;
	t_cp	*haha;

	buff = NULL;
	if (ft_cmp(cdm->command) == 0)
		buff = ft_strjoinn(cdm->command, cdm->args);
	if (cdm->next->fields[1])
		buff = ft_strjoinnfree(&buff, &cdm->next->fields[1], " ");
	haha = cdm->next;
	while (haha && haha->next)
	{
		buff = ft_strjoinnfree(&buff, haha->next->fields, " ");
		haha = haha->next;
	}
	if (buff)
		return (create_command(buff, 1));
	else
		return (NULL);
}

void	ft_droite(t_cp *cdm, int mode)
{
	int		fd;
	t_cp	*haha;

	fd = open(cdm->next->command, mode, 0777);
	if (fd < 0)
		return (perror(strerror(errno)));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	haha = la_commande_sans_la_fleche(cdm);
	if (haha)
		execute(haha);
}

void	ft_extreme_droite(t_cp *cmd_line)
{
	ft_droite(cmd_line, O_RDWR | O_CREAT | O_APPEND);
}

void	ft_pipe(t_cp *cmd_line)
{
	char	**a;
	t_cp	*b;

	a = cmd_line->fields;
	b = cmd_line;
	while (b)
	{
		if (b->fields[ft_strrlen(b->fields) - 1][0] == '|')
		{
			a = b->fields;
			break ;
		}
		b = b->next;
	}
	if (ft_cmp(a[ft_strrlen(a) - 1]) == 1)
		ft_droite(cmd_line, O_WRONLY | O_CREAT | O_TRUNC);
	else if (ft_cmp(a[ft_strrlen(a) - 1]) == 2)
		ft_gauche(cmd_line);
	else if (ft_cmp(a[ft_strrlen(a) - 1]) == 3)
		ft_pipex(cmd_line);
	else if (ft_cmp(a[ft_strrlen(a) - 1]) == 4)
		ft_extreme_droite(cmd_line);
	else if (ft_cmp(a[ft_strrlen(a) - 1]) == 5)
		ft_extreme_gauche(cmd_line);
	(dup2(g_vars->outstd, STDOUT_FILENO), dup2(g_vars->instd, STDIN_FILENO));
}
