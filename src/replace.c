/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ^@^ Foxan ^@^ <thibaut.unsinger@gmail.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 11:10:37 by ^@^ Foxan ^@^     #+#    #+#             */
/*   Updated: 2023/03/04 11:10:38 by ^@^ Foxan ^@^    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_env(char *str, int *i)
{
	int		j;
	char	*var;
	char	*res;
	char	*res2;

	res = ft_strldup(str, *i);
	var = find_var(str, &j, *i);
	if (var)
	{
		res2 = ft_strjoin(res, var);
		free(res);
		res = ft_strjoin(res2, &str[j]);
		*i += ft_strlen(var) - 1;
		free(var);
		free(res2);
		free(str);
		return (res);
	}
	else
	{
		res2 = ft_strjoin(res, &str[j]);
		free(res);
		free(str);
		return (res2);
	}
}

char	*find_var(char *str, int *j, int i)
{
	char	*var_name;
	char	*var;

	*j = i + 1;
	while (is_alnumscore(str[*j]))
		(*j)++;
	var_name = ft_strldup(&str[i + 1], *j - i - 1);
	var = ft_getenv(var_name);
	free(var_name);
	return (var);
}

char	*replace_home(char *str, int *i)
{
	char	*var;
	char	*res;
	char	*res2;

	res = ft_strldup(str, *i);
	var = ft_getenv("HOME");
	if (var)
	{
		res2 = ft_strjoin(res, var);
		free(res);
		res = ft_strjoin(res2, &str[*i + 1]);
		*i += ft_strlen(var);
		free(var);
		free(res2);
		free(str);
		return (res);
	}
	else
	{
		res2 = ft_strjoin(res, &str[*i + 1]);
		free(res);
		free(str);
		return (res2);
	}
}

char	*replace_status(char *str, int *i)
{
	char	*var;
	char	*res;
	char	*res2;

	res = ft_strldup(str, *i);
	var = ft_itoa(g_vars->last_status);
	if (var)
	{
		res2 = ft_strjoin(res, var);
		free(res);
		res = ft_strjoin(res2, &str[*i + 2]);
		*i += strlen(var) - 1;
		free(var);
		free(res2);
		free(str);
		return (res);
	}
	else
	{
		res2 = ft_strjoin(res, &str[*i + 2]);
		free(res);
		free(str);
		return (res2);
	}
}
