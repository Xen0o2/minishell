/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:23:06 by mdoumi            #+#    #+#             */
/*   Updated: 2023/05/15 16:00:30 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	afficher_tab(t_line **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		afficher_line(tab[i]);
		i++;
	}
}

void	afficher_line(t_line *line)
{
	int	i;

	printf("Raw :     %s\n", line->raw);
	printf("Raw ss :  %s\n", line->raw_sans_sep);
	printf("\nCommand : %s\n", line->command);
	printf("Args :    %s\n", line->args[0]);
	i = 1;
	while (line->args[i])
		printf("          %s\n", line->args[i++]);
	i = 1;
	printf("\nFields :  %s\n", line->fields[0]);
	while (line->fields[i])
		printf("          %s\n", line->fields[i++]);
	printf("\nSep :     %s\n", line->sep);
}

t_line	*fill_line(char *str, int *i, int *j)
{
	t_line	*clean;
	int		count;
	int		z;

	clean = malloc(sizeof(t_line));
	count = *i;
	while (str[*i] && is_sep(str[*i]))
		(*i)++;
	if (*i - count > 2)
		printf("Error\nInvalid pipe error.\n");
	clean->raw = ft_substr(str, *j, *i - *j);
	clean->sep = ft_substr(str, count, *i - count);
	clean->raw_sans_sep = ft_substr(str, *j, (*i - *j) - (*i - count));
	clean->fields = better_split(clean->raw_sans_sep, is_white);
	clean->command = ft_strdup(clean->fields[0]);
	clean->raw_sans_com = ft_substr(str, ft_strlen(clean->command) + *j, *i - count);
	clean->args = malloc(sizeof(char *) * ft_strrlen(clean->fields));
	z = 0;
	while (clean->fields[++z])
		clean->args[z - 1] = ft_strdup(clean->fields[z]);
	while (str[*i] && is_white(str[*i]))
		(*i)++;
	return (clean);
}

int	ft_cleanlen(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (1)
	{
		if (is_sep(str[i]) || !str[i])
		{
			while (str[i] && is_sep(str[i]))
				i++;
			count++;
		}
		if (!str[i])
			break ;
		i++;
	}
	return (count);
}

t_line	**parse_line(char *str)
{
	int		i;
	int		j;
	int		k;
	t_line	**tab;

	tab = malloc(sizeof(t_line) * ft_cleanlen(str) + 1);
	i = 0;
	j = 0;
	k = 0;
	while (1)
	{
		if (is_sep(str[i]) || !str[i])
		{
			tab[k++] = fill_line(str, &i, &j);
			j = i;
		}
		if (!str[i])
			break ;
		i++;
	}
	tab[k] = NULL;
	return (tab);
}
