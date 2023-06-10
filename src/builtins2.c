/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:06:38 by ^@^ Foxan ^       #+#    #+#             */
/*   Updated: 2023/04/12 18:51:32 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	g_vars->last_status = errno;
	printf("%s\n", path);
	free(path);
}

void	ft_cd(char *path)
{
	if (chdir(path) == -1)
		perror(strerror(errno));
	g_vars->last_status = 1;
}

void	ft_echo(char **fields)
{
	int	i;
	int	j;
	int	in_q;

	in_q = 0;
	if (fields && fields[0])
	{
		i = is_n(fields) - 1;
		while (fields[++i])
		{
			j = -1;
			while (fields[i][++j])
				printf("%c", fields[i][j] - (fields[i][j]
						* (fields[0][0] == ' ' && fields[0][1] == 0)));
			if (fields[i + 1])
				printf(" ");
		}
		if (!is_n(fields))
			printf("\n");
	}
	else
		printf("\n");
	g_vars->last_status = 0;
}

int	update(char c, int *in_q)
{
	if (c == '\'' && *in_q != 2)
	{
		*in_q = 1 - (1 * (*in_q == 1));
		return (1);
	}
	if (c == '\"' && *in_q != 1)
	{
		*in_q = 2 - (2 * (*in_q == 2));
		return (1);
	}
	return (0);
}

int	is_n(char **fields)
{
	int	i;
	int	j;

	i = -1;
	while (fields[++i])
	{
		if (fields[i][0] != '-')
			return (i);
		j = 0;
		while (fields[i][++j])
			if (fields[i][j] != 'n')
				return (i);
	}
	return (i);
}
