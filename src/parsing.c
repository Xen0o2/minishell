/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:37:31 by ^@^ Foxan ^       #+#    #+#             */
/*   Updated: 2023/04/12 18:39:30 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cp	*parse_line(char *line)
{
	t_arguments4	a;

	((void)0, a.end = -1, a.start = 0, a.in_q = 0);
	a.cmds = NULL;
	a.str = ft_strdup(line);
	space_arrows(&a.str);
	substitute(&a.str);
	while (a.str[++a.end])
	{
		if (a.str[a.end] == '\'' && a.in_q != 2)
			a.in_q = 1 - (1 * (a.in_q == 1));
		if (a.str[a.end] == '\"' && a.in_q != 1)
			a.in_q = 2 - (2 * (a.in_q == 2));
		a.type = is_sep(&a.str[a.end]);
		if (a.type && a.in_q == 0 && a.end++ > -1)
		{
			append(&a.cmds, new_part(ft_strldup(&a.str[a.start],
						a.end - a.start + is_dsep(a.type))));
			a.start = a.end + is_dsep(a.type);
		}
	}
	append(&a.cmds, new_part(ft_strldup(&a.str[a.start],
				a.end - a.start)));
	free(a.str);
	return (a.cmds);
}

t_cp	*parse_commands(t_cp *commands)
{
	t_arguments	a;

	a.tmp = commands;
	while (a.tmp)
	{
		a.tmp->fields = parse_command(a.tmp->str);
		if (!a.tmp->fields)
			return (NULL);
		a.tmp->command = ft_strdup(a.tmp->fields[0]);
		if (!a.tmp->fields[1])
		{
			a.buff = ft_strdup(" \n");
			a.tmp->args = ft_split(a.buff, '\n');
			free(a.buff);
		}
		else
			a.tmp->args = ft_strrdup(&a.tmp->fields[1]);
		a.len = ft_strrlen(a.tmp->args) - 1;
		if (is_sep(a.tmp->args[a.len]))
			reset_args(a.tmp, a.len);
		a.tmp = a.tmp->next;
	}
	return (commands);
}

char	**parse_command(char *command)
{
	char	**fields;
	char	*str;
	int		i;

	i = -1;
	str = ft_strdup(command);
	fields = ft_splitargs(str, ' ');
	if (!fields)
		return (NULL);
	if (!fields[0])
		return (free(fields), NULL);
	while (fields[++i])
		trim_quotes(&fields[i]);
	free(str);
	return (fields);
}

void	substitute(char **field)
{
	int		i;
	int		in_q;

	i = 0;
	in_q = 0;
	while ((*field)[i])
	{
		if ((*field)[i] == '\'' && in_q != 2)
			in_q = 1 - (1 * (in_q == 1));
		if ((*field)[i] == '\"' && in_q != 1)
			in_q = 2 - (2 * (in_q == 2));
		if ((*field)[i] == '$' && in_q != 1)
		{
			if (is_alpha((*field)[i + 1]) || (*field)[i + 1] == '_')
				*field = replace_env(*field, &i);
			else if ((*field)[i + 1] == '?')
				*field = replace_status(*field, &i);
		}
		if ((*field)[i] == '~' && ((*field)[i + 1] == '/'
			|| (*field)[i + 1] == ' ' || !(*field)[i + 1]))
			*field = replace_home(*field, &i);
		i++;
	}
}

void	trim_quotes(char **field)
{
	int		i;
	int		j;
	int		in_q;
	char	*res;
	char	*res2;

	i = 0;
	j = -1;
	in_q = 0;
	res = malloc(sizeof(char) * (ft_strlen(*field) + 1));
	while ((*field)[i])
	{
		while ((*field)[i] && update((*field)[i], &in_q))
			i++;
		res[++j] = (*field)[i];
		if ((*field)[i])
			i++;
	}
	res[++j] = '\0';
	res2 = ft_strdup(res);
	free(res);
	free((*field));
	*field = res2;
}
