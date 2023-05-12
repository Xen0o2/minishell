/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:28:50 by mdoumi            #+#    #+#             */
/*   Updated: 2023/05/12 18:58:37 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_white(char c)
{
	if (c == ' ' || c == '\r' || c == '\t' || c == '\n' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	check_line(char *str)
{
	int	i;
	int	is_valid;

	i = 0;
	is_valid = 0;
	while (str[i])
	{
		if (!is_white(str[i]))
			is_valid = 1;
		i++;
	}
	return (is_valid);
}

void	ft_exit()
{
	exit(0);
}

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_lower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ('A' < str[i] && str[i] <= 'Z')
			str[i] += 'a' - 'A';
		i++;
	}
	return (str);
}

void	launch_command(char *str)
{
	if (ft_strcmp(ft_lower(str), "exit") == 0)
		ft_exit();
	else if (ft_strcmp(ft_lower(str), "export") == 0)
	{}
	else if (ft_strcmp(ft_lower(str), "unset") == 0)
	{}
	else if (ft_strcmp(ft_lower(str), "echo") == 0)
	{}
	else if (ft_strcmp(ft_lower(str), "cd") == 0)
	{}
	else if (ft_strcmp(ft_lower(str), "pwd") == 0)
	{}
	else if (ft_strcmp(ft_lower(str), "env") == 0)
	{}

}

int	ft_strrlen(char **strr)
{
	int	i;

	i = 0;
	while (strr && strr[i])
		i++;
	return (i);
}

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

void	init_global(char **env)
{
	global = malloc(sizeof(t_glo));

	global->env = ft_strrdup(env);
}

// int	main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	(void)env;

// 	char *line;
// 	int	run;

// 	init_global(env);
// 	run = 1;
// 	while (run)
// 	{
// 		if (line)
// 			free(line);
// 		line = readline("minishell ");
// 		if (check_line(line))
// 		{
// 			launch_command(line);
// 		}
// 	}
// }
