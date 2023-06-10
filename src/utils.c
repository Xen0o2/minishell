/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:01:03 by mdoumi            #+#    #+#             */
/*   Updated: 2023/06/10 15:37:49 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_sep(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

int	is_white(char c)
{
	if (c == ' ' || c == '\r' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f')
		return (1);
	return (0);
}

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}
