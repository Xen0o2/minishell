/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:24:55 by alecoutr          #+#    #+#             */
/*   Updated: 2023/05/12 19:41:47 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static    int    ft_wordcount(char *s, char c)
{
    int    i;
    int    cmp;

    i = -1;
    cmp = 0;
    if (s[i + 1] != c)
        cmp++;
    while (s[++i])
        if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
            cmp++;
    return (cmp);
}

static    char    *ft_putword(char *s, char c, int i)
{
    int    j;

    j = i;
    while (s[j] && s[j + 1] != c)
        j++;
    return (ft_substr(s, i, j - i + 1));
}

static    void    free_all(char **rep, int j)
{
    while (j >=0)
    {
        free(rep[j]);
        j--;
    }
    free(rep);
}

char    *ft_substr(char *s, int start, int len)
{
    int    i;
    char    *rep;

    if (!s)
        return (NULL);
    if (start < ft_strlen(s))
        len = len + start;
    if (len > ft_strlen(s))
        len = ft_strlen(s);
    if (start < len)
        rep = malloc(sizeof(char) * (len - start + 1));
    else
        rep = malloc(sizeof(char));
    if (rep == NULL)
        return (NULL);
    i = start;
    while (i < len && s[i] != '\0')
    {
        rep[i - start] = s[i];
        i++;
    }
    rep[i - start] = '\0';
    return (rep);
}

char    **ft_split(char *s, char c)
{
    int        i;
    int        j;
    char    **rep;

    if (!s)
        return (NULL);
    i = -1;
    j = 0;
    rep = malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
    if (!rep)
        return (NULL);
    while (s[++i])
    {
        if (s[i] != c && i == 0)
            rep[j++] = ft_putword(s, c, i++);
        if (s[i] == c && s[i + 1] != c && s[i + 1])
            rep[j++] = ft_putword(s, c, i + 1);
        if (!rep[j - 1])
        {
            free_all(rep, j - 1);
            return (NULL);
        }
    }
    rep[j] = NULL;
    return (rep);
}