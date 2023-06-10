/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 10:39:30 by ^@^ Foxan ^       #+#    #+#             */
/*   Updated: 2023/03/23 06:17:38 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verif_line(char *line)
{
	struct s_arguments3	a;

	a.i = -1;
	a.nb_q = 0;
	a.in_q = 0;
	a.j = -1;
	while (line[++a.j] && ((9 <= line[a.j] && line[a.j] <= 13)
			|| line[a.j] == 32 || line[a.j] == 127));
	if (line[a.j] && is_sep(&line[a.j]) == 1)
		return (0);
	while (line[++a.i])
	{
		update(line[a.i], &a.in_q);
		a.nb_q += (line[a.i] == '\'' && a.in_q != 2)
			+ (line[a.i] == '\"' && a.in_q != 1);
		if (!verify_sep(&line[a.i]))
			return (0);
	}
	a.j = ft_strlen(line);
	while (--a.j > 0 && ((9 <= line[a.j] && line[a.j] <= 13) || line[a.j] == 32
			|| line[a.j] == 127));
	if (a.j < 0 || is_sep(&line[a.j]))
		return (0);
	return (a.nb_q % 2 == 0);
}

int	is_alnumscore(char c)
{
	return (('0' <= c && c <= '9')
		|| ('A' <= c && c <= 'Z')
		|| ('a' <= c && c <= 'z')
		|| (c == '_'));
}

int	is_alpha(char c)
{
	return (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'));
}

int	is_simple_sep(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	verify_sep(char *str)
{
	if (!is_sep(&str[0]) || is_sep(&str[0]) == 1)
		return (1);
	else if (is_sep(&str[0]) % 2 == 0 && !next_is_sep(&str[1]))
		return (1);
	else if (is_sep(&str[0]) % 2 == 1 && !next_is_sep(&str[2]))
		return (1);
	g_vars->last_status = 258;
	return (0);
}
