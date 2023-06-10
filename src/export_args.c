/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:46:49 by alecoutr          #+#    #+#             */
/*   Updated: 2023/05/18 21:05:00 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	invalid_char_in_arg(char *arg)
{
	int		i;
	int		x;
	char	*invalid_char;

	i = 0;
	invalid_char = "$#+-/@.^%!-?.,;:{}[]&";
	while (arg[i] && arg[i] != '=')
	{
		x = -1;
		while (invalid_char[++x])
			if (arg[i] == invalid_char[x])
				return (1);
		i++;
	}
	return (0);
}

int	is_valid_arg(char *arg)
{		
	if (arg[0] >= '0' && arg[0] <= '9')
		return (printf("export: `%s': not a valid identifier\n"
				, arg), 0);
	if (invalid_char_in_arg(arg))
		return (printf("export: `%s': not a valid identifier\n"
				, arg), 0);
	return (1);
}

int	equal_split(char c)
{
	return (c == '=');
}

void	add_arg(char *arg)
{
	int	i;

	i = realloc_env();
	g_lobal->env[i] = ft_strdup(arg);
	g_lobal->env[i + 1] = NULL;
}
