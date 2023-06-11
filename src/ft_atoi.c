/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:41:47 by alecoutr          #+#    #+#             */
/*   Updated: 2023/06/10 15:41:49 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(char c);

static int	ft_isop(char c);

static int	ft_isnbr(char c);

int	ft_atoi(char *str)
{
	int	i;
	int	s;
	int	r;
	int	d;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	s = 1;
	if (ft_isop(str[i]))
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	r = 0;
	d = 1;
	while (ft_isnbr(str[i]))
	{
		r *= 10;
		r += str[i] - '0';
		i++;
		d *= 10;
	}
	return (r * s);
}

static int	ft_isspace(char c)
{
	if (c == '\0')
		return (0);
	if (c == '\t')
		return (1);
	if (c == '\n')
		return (1);
	if (c == '\v')
		return (1);
	if (c == '\f')
		return (1);
	if (c == '\r')
		return (1);
	if (c == ' ')
		return (1);
	return (0);
}

static int	ft_isop(char c)
{
	if (c == '\0')
		return (0);
	if (c == '+')
		return (1);
	if (c == '-')
		return (1);
	return (0);
}

static int	ft_isnbr(char c)
{
	if (c == '\0')
		return (0);
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
