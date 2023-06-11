/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitargs_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:42:07 by alecoutr          #+#    #+#             */
/*   Updated: 2023/06/10 15:42:08 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_sep(char *sep, char c, const char *s1, int len)
{
	if ((s1[len] == '\'' || s1[len] == '\"') && *sep == c)
		*sep = s1[len];
	else if ((s1[len] == '\'' || s1[len] == '\"') && *sep == s1[len])
		*sep = c;
}

void	insert_space(char **str, int i)
{
	char	*p1;
	char	*p2;
	char	*p3;

	p1 = ft_strldup(*str, i + 1);
	p3 = ft_strdup(&((*str)[i + 1]));
	free(*str);
	p2 = ft_strjoin(p1, " ");
	free(p1);
	*str = ft_strjoin(p2, p3);
	free(p2);
	free(p3);
}

void	space_arrows(char **field)
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
		if (is_sep(&(*field)[i]))
		{
			if ((*field)[i - 1] && (*field)[i - 1] != ' '
				&& !(is_simple_sep((*field)[i - 1])))
				(insert_space(field, i - 1), i++);
			if ((*field)[i + 1] && (*field)[i + 1] != ' '
				&& !(is_simple_sep((*field)[i + 1])))
				insert_space(field, i);
		}
		i++;
	}
}
