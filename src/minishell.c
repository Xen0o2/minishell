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

void	launch_command(t_line *line)
{
	if (ft_strcmp(ft_lower(line->command), "exit") == 0)
		ft_exit(line->args);
	else if (ft_strcmp(ft_lower(line->command), "export") == 0)
	{
	}
	else if (ft_strcmp(ft_lower(line->command), "unset") == 0)
	{
	}
	else if (ft_strcmp(ft_lower(line->command), "echo") == 0)
	{
	}
	else if (ft_strcmp(ft_lower(line->command), "cd") == 0)
		//ft_cd(line->args);
	{
	}
	else if (ft_strcmp(ft_lower(line->command), "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(ft_lower(line->command), "env") == 0)
		ft_env();
	else
		printf("Command not found.\n");
}

void	execute(t_line **tab)
{
	if (ft_tablen(tab) > 1)
	{
		//Lancer les pipes
	}
	else
	{
		launch_command(tab[0]);
	}
}

void	init_global(char **env)
{
	g_lobal = malloc(sizeof(t_glo));
	g_lobal->env = ft_strrdup(env);
	g_lobal->last_status = 0;
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_line	**tab;
	int		run;

	(void)ac;
	(void)av;
	init_global(env);
	run = 1;
	while (run)
	{
		if (line)
			free(line);
		line = readline("minishell ");
		if (check_line(line))
		{
			tab = parse_line(line);
			//afficher_line(tab[0]);
			execute(tab);
		}
	}
}
