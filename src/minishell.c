#include "minishell.h"

int	check_line(char *str)
{
	int	i;
	int	is_valid;

	i = 0;
	is_valid = 0;
	while (str[i])
	{
		if (!is_white(str[i]))
			is_valid = 1;
		i++;
	}
	return (is_valid);
}

char	*ft_lower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ('A' < str[i] && str[i] <= 'Z')
			str[i] += 'a' - 'A';
		i++;
	}
	return (str);
}

void	launch_command(char *str)
{
	if (ft_strcmp(ft_lower(str), "exit") == 0)
		ft_exit();
	else if (ft_strcmp(ft_lower(str), "export") == 0)
	{
	}
	else if (ft_strcmp(ft_lower(str), "unset") == 0)
	{
	}
	else if (ft_strcmp(ft_lower(str), "echo") == 0)
	{
	}
	else if (ft_strcmp(ft_lower(str), "cd") == 0)
	{
		ft_cd(str);
	}
	else if (ft_strcmp(ft_lower(str), "pwd") == 0)
	{
		ft_pwd();
	}
	else if (ft_strcmp(ft_lower(str), "env") == 0)
	{
		ft_env();
	}
	else
		printf("Command not found.\n");
}

void	init_global(char **env)
{
	g_lobal = malloc(sizeof(t_glo));
	g_lobal->env = ft_strrdup(env);
	g_lobal->last_status = 0;
}

// int	main(int ac, char **av, char **env)
// {
// 	char	*line;
// 	t_line	**tab;
// 	int		run;

// 	(void)ac;
// 	(void)av;
// 	init_global(env);
// 	run = 1;
// 	while (run)
// 	{
// 		if (line)
// 			free(line);
// 		line = readline("minishell ");
// 		if (check_line(line))
// 		{
// 			tab = parse_line(line);
// 			afficher_line(tab[0]);
// 			//launch_command(tab);
// 		}
// 	}
// }
