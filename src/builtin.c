/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:34:47 by mdoumi            #+#    #+#             */
/*   Updated: 2023/05/15 16:34:52 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **args)
{
	int	i;

	i = 0;
	if (check_exit(char **args))
		return ;
	while (g_lobal->env[i])
		free(g_lobal->env[i++]);
	free(g_lobal->env);
	free(g_lobal);
	exit(0);
}

void	ft_env(void)
{
	int	i;

	i = 0;
	while (g_lobal->env[i])
		printf("%s\n", g_lobal->env[i++]);
}

void	ft_pwd(void)
{
	char	*str;

	str = getcwd(NULL, 0);
	g_lobal->last_status = errno;
	printf("%s\n", str);
	free(str);
}

void	ft_cd(char *path)
{
	if (chdir(path) == -1)
		perror(strerror(errno));
}
