/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:06:02 by mdoumi            #+#    #+#             */
/*   Updated: 2023/05/14 18:32:35 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	next_word_length(char const *s, int (*cmp)(char c))
{
	int	length;

	length = 0;
	while (*s && cmp(*s))
		s++;
	while (*s && !cmp(*s))
	{
		s++;
		length++;
	}
	return (length);
}

static int	get_sep_nbr(char const *s, int (*cmp)(char c))
{
	int	count;

	count = 0;
	while (*s)
	{
		while (cmp(*s))
			s++;
		if (!cmp(*s) && *s)
		{
			count++;
			while (!cmp(*s) && *s)
				s++;
		}
	}
	return (count + 1);
}

static char	*create_malloc(char **tab, int length)
{
	*tab = malloc((length + 1) * sizeof(char));
	if (!*tab)
		return (NULL);
	return (*tab);
}

static char	**ft_freeall(char **tab, int length)
{
	int	i;

	i = 0;
	while (i < length)
		free(tab[i++]);
	free(tab);
	return (0);
}

char	**better_split(char const *s, int (*cmp)(char c))
{
	t_split	all;

	if (!s)
		return (0);
	all.sep = get_sep_nbr(s, cmp);
	all.tab = malloc(all.sep * sizeof(char *));
	if (!all.tab)
		return (NULL);
	all.i = 0;
	while (all.i < all.sep - 1)
	{
		all.j = 0;
		while (*s && cmp(*s))
			s++;
		all.length = next_word_length(s, cmp);
		if (!create_malloc(&all.tab[all.i], all.length))
			return (ft_freeall(all.tab, all.i));
		while (all.j < all.length)
			all.tab[all.i][all.j++] = *s++;
		all.tab[all.i++][all.j] = 0;
	}
	all.tab[all.i] = 0;
	return (all.tab);
}
