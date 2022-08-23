/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 20:59:55 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/08/23 16:29:47 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parser(char *input, t_env *enviro)
{
	t_list	*tokens;
	(void)enviro;
	if (quote_checker(input) == -1)
		fprintf(stderr, "QUOTE_ERROR\n");
	tokens = tokens_split(input);
	while (tokens)
	{
		printf("token->value: |%s|\ntoken->type: %d\n",
			((t_token *)tokens->content)->value,
			((t_token *)tokens->content)->type);
		tokens = tokens->next;
	}
}

void	chose(t_env *enviro, t_cmd *cmd)
{
	if (ft_strncmp(cmd->name, "exit", 4) == 0)
	{
		free(cmd);
		exitfree(enviro);
	}
	else if (ft_strncmp(cmd->name, "pwd", 3) == 0)
		pwd();
	else if (ft_strncmp(cmd, "env", 3) == 0)
		envi(enviro);
	else if (ft_strncmp(cmd>name, "export", 6) == 0)
	{
		cmd = cmd + 7;
		export(cmd, enviro);
	}
	else if (ft_strncmp(cmd>name, "unset", 5) == 0)
	{
		cmd = cmd + 6;
		unset(cmd, enviro);
	}
	else if (ft_strncmp(cmd>name, "cd", 2) == 0)
	{
		cmd = cmd + 2;
		cd(cmd, enviro);
	}
	else if (ft_strncmp(cmd>name, "echo ", 5) == 0)
	{
		cmd = cmd + 5;
		echo(cmd, enviro, 0);
	}
	else if (ft_strncmp(cmd>name, "./", 2) == 0)
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
