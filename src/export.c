/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:48:24 by alecoutr          #+#    #+#             */
/*   Updated: 2023/05/12 19:46:36 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    export_without_args()
{
    int     i;
    char    **env;

    i = -1;
    while (global->env[++i])
    {
        env = ft_split(global->env[i], '=');
        if (env[1])
            printf("declare -x %s=\"%s\"\n", env[0], env[1]);
        else
            printf("declare -x %s\n", env[0]);
    }
    i = -1;
    while (env[++i])
        free(env[i]);
}

void    export(char **args)
{
    // args = {"ac=salut", "ab"};
    char    **tmp;
    int     i;
    int     length;

    i = 0;
    while (args[i])
        i++;
    if (i == 0)
        export_without_args();
    else
    {
        tmp = ft_strrdup(global->env);
        length = 0;
        while (global->env[length])
            length++;
        free(global->env);
        global->env = malloc(sizeof(char *) * (length + i));
        i = -1;
        while (tmp[++i])
            global->env[i] = tmp[i];
        i = -1;
        while (args[++i])
            global->env[length + i] = ft_strdup(args[i]);
    }
}

void    print_env(void)
{
    int i;

    i = -1;
    printf("env\n");
    while (global->env[++i])
        printf("%s\n", global->env[i]);
}

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    global = malloc(sizeof(t_glo));

    global->env = ft_strrdup(env);
    
    // char *str[3] = {"username=alecoutr", "password", NULL};
    char *stre[0] = {};
    // export(str);
    export(stre);
}
