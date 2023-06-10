/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitargs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:01:46 by ^@^ Foxan ^       #+#    #+#             */
/*   Updated: 2023/02/24 22:09:45 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	count_words(const char *s, char c);
static char	**single_word(const char *s, char c);
static char	*dupstr(const char *s1, char c, int *i);
static void	freel(char **str, int n);

char	**ft_splitargs(const char *s, char c)
{
	char	**res;
	int		i;
	int		j;

	if (count_words(s, c) == 1)
		return (single_word(s, c));
	res = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i] && j < count_words(s, c))
	{
		while (s[i] != 0 && s[i] == c && s[i] != '\'' && s[i] != '\"')
			i++;
		res[j] = dupstr(&s[i], c, &i);
		if (res[j] == NULL)
		{
			freel(res, j);
			return (NULL);
		}
		j++;
	}
	res[j] = NULL;
	return (res);
}

static int	count_words(const char *s, char c)
{
	int		i;
	int		count;
	int		last;
	char	sep;

	i = 0;
	count = 0;
	last = 1;
	sep = c;
	while (s[i])
	{
		set_sep(&sep, c, s, i);
		if (s[i] != sep)
		{
			if (last == 1)
				count++;
			last = 0;
		}
		else
			last = 1;
		i++;
	}
	return (count);
}

static char	**single_word(const char *s, char c)
{
	char	**res;
	int		i;

	i = 0;
	while (s[i] == c)
		i++;
	res = malloc(2 * sizeof(char *));
	if (res == NULL)
		return (NULL);
	res[0] = dupstr(&s[i], c, NULL);
	res[1] = NULL;
	if (res[0] == NULL)
	{
		free(res);
		return (NULL);
	}
	return (res);
}

static char	*dupstr(const char *s1, char c, int *i)
{
	char	*s2;
	int		len;
	char	sep;

	len = 0;
	sep = c;
	while (s1[len] && (s1[len] != c || sep != c))
	{
		set_sep(&sep, c, s1, len);
		len++;
	}
	s2 = malloc((len + 1) * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	len = 0;
	while (s1[len] && (s1[len] != c || sep != c))
	{
		set_sep(&sep, c, s1, len);
		s2[len] = s1[len];
		len++;
	}
	s2[len] = '\0';
	if (i != NULL)
		*i += len - 1;
	return (s2);
}

static void	freel(char **str, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(str[i]);
		i++;
	}
	free(str);
}
