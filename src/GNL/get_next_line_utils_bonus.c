/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <thibaut.unsinger@gmail.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:33:29 by alecoutr     #+#    #+#             */
/*   Updated: 2022/11/10 11:33:31 by alecoutr    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(const char *str)
{
	int	len;

	if (str == NULL)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strlcpy(const char *src, char *dst, int n)
{
	int	i;

	i = 0;
	if (src == NULL || dst == NULL)
		return (NULL);
	while (i < n && src[i] != 0)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

unsigned int	ft_strlcat(const char *src, char *dst, unsigned int dstsize)
{
	unsigned int	srcsize;
	unsigned int	dstlen;
	unsigned int	i;

	srcsize = ft_strlen(src);
	dstlen = ft_strlen(dst);
	i = 0;
	if (dstsize > dstlen)
	{
		while (i < dstsize - dstlen - 1 && src[i] != 0)
		{
			dst[i + dstlen] = src[i];
			i++;
		}
		dst[i + dstlen] = '\0';
	}
	if (dstsize < dstlen)
		return (srcsize + dstsize);
	return (srcsize + dstlen);
}
