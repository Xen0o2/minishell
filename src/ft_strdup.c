/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:11:42 by mdoumi            #+#    #+#             */
/*   Updated: 2023/05/14 19:13:32 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *s1)
{
	char	*s2;
	int		len;

	len = 0;
	while (s1[len])
		len++;
	s2 = malloc((len + 1) * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	len = 0;
	while (s1[len])
	{
		s2[len] = s1[len];
		len++;
	}
	s2[len] = '\0';
	return (s2);
}

char	**ft_strrdup(char **s1)
{
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * (ft_strrlen(s1) + 1));
	i = 0;
	while (s1[i])
	{
		res[i] = ft_strdup(s1[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}
