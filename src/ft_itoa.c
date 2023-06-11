/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:41:54 by alecoutr          #+#    #+#             */
/*   Updated: 2023/06/10 15:41:56 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	lenint(int n);
static int	signe(const int *n, int *s);

char	*ft_itoa(int n)
{
	char			*res;
	unsigned int	nb;
	int				s;
	int				i;

	nb = signe(&n, &s);
	res = malloc(lenint(nb) + s + 1);
	if (res == NULL)
		return (NULL);
	res[lenint(nb) + s] = '\0';
	if (n == 0)
	{
		res[0] = '0';
		return (res);
	}
	if (s)
		res[0] = '-';
	i = lenint(nb) - 1 + s;
	while (nb > 0)
	{
		res[i] = '0' + nb % 10;
		i--;
		nb /= 10;
	}
	return (res);
}

static int	lenint(int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static int	signe(const int *n, int *s)
{
	*s = 0;
	if (*n < 0)
	{
		*s = 1;
		return (-(*n));
	}
	return (*n);
}
