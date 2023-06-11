/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fordprefect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:16:32 by ^@^ Foxan ^       #+#    #+#             */
/*   Updated: 2023/06/11 17:58:39 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*for debug purposes*/
void	print_line(t_cp *line)
{
	t_cp	*tmp;
	int		i;

	tmp = line;
	printf("---\n");
	while (tmp)
	{
		printf("str : %s\n", tmp->str);
		printf("command : %s\n", tmp->command);
		i = -1;
		printf(" fields:\n");
		while (tmp->fields && tmp->fields[++i])
			printf("  -%s\n", tmp->fields[i]);
		i = -1;
		printf(" args:\n");
		while (tmp->args && tmp->args[++i])
			printf("  -%s\n", tmp->args[i]);
		tmp = tmp->next;
	}
	printf("---\n");
}
