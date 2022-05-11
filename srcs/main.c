/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 20:59:55 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/05/11 16:31:49 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(char *cmd, t_env *enviro)
{
	char	*print;

	print = NULL;
	if (cmd == NULL)
		exitfree(enviro);
	else if (ft_strncmp(cmd, "exit", 4) == 0)
	{
		free(cmd);
		exitfree(enviro);
	}
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		pwd();
	else if (ft_strncmp(cmd, "env", 3) == 0)
		envi(enviro);
	else if (ft_strncmp(cmd, "export", 6) == 0)
	{
		cmd = cmd + 7;
		export(cmd, enviro);
	}
	else if (ft_strncmp(cmd, "unset", 5) == 0)
	{
		cmd = cmd + 6;
		unset(cmd, enviro);
	}
	else if (ft_strncmp(cmd, "cd", 2) == 0)
	{
		cmd = cmd + 2;
		cd(cmd, enviro);
	}
	else if (ft_strncmp(cmd, "echo ", 5) == 0)
	{
		cmd = cmd + 5;
		echo(cmd, enviro, 0);
	}
	else if (ft_strncmp(cmd, "./", 2) == 0)
	{
		cmd = cmd + 1;
		exed(cmd, enviro);
	}
	else
		lexe(cmd, enviro);
}

void	ctrlc(int i)
{
	signal(SIGINT, ctrlc);
	i = i + 5;
	rl_on_new_line();
	rl_replace_line("", 1);
	printf("\n");
	rl_redisplay();
}

int	main(int ac, char **av, char **env)
{
	char	*cmd;
	t_env	*enviro;

	(void) ac;
	(void) av;
	enviro = initenv(env);
	while (1)
	{
		signal(SIGINT, ctrlc);
		signal(SIGQUIT, SIG_IGN);
		cmd = readline("minishell% ");
		if (cmd && ft_strlen(cmd) > 0)
			add_history(cmd);
		parsing(cmd, enviro);
		free(cmd);
	}
	return (0);
}
