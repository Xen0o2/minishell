/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:11:02 by mdoumi            #+#    #+#             */
/*   Updated: 2023/04/12 17:12:50 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipe_chart(int right, int left, int pipe)
{
	if (right == 1)
		return (1);
	if (left == 1)
		return (2);
	if (pipe == 1)
		return (3);
	if (right == 2)
		return (4);
	if (left == 2)
		return (5);
	return (0);
}

int	ft_cmp(char *str)
{
	int	i;
	int	right;
	int	left;
	int	pipe;

	i = -1;
	right = 0;
	left = 0;
	pipe = 0;
	while (str[++i])
	{
		if (str[i] == '>')
			right++;
		if (str[i] == '<')
			left++;
		if (str[i] == '|')
			pipe++;
	}
	return (ft_pipe_chart(right, left, pipe));
}

void	printe(char *str)
{
	dup2(g_vars->outstd, STDOUT_FILENO);
	printf("%s", str);
}

char	*ft_enlever_redirection(char *str)
{
	int		i;
	char	*cpy;

	i = 0;
	cpy = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[i])
	{
		if (is_sep(&str[i]))
			break ;
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
