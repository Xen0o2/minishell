/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ^@^ Foxan ^@^ <thibaut.unsinger@gmail.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:09:45 by ^@^ Foxan ^@^     #+#    #+#             */
/*   Updated: 2023/04/13 14:09:46 by ^@^ Foxan ^@^    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_only_spaces(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
		if (str[i] != ' ')
			return (0);
	return (1);
}

int	is_dsep(int s)
{
	return (s == 3 || s == 5);
}

int	next_is_sep(char *str)
{
	int	j;

	j = 0;
	while (str[j] == ' ')
		j++;
	return (is_sep(&str[j]));
}
