/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 20:59:55 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/08/30 18:18:16 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parser(char *input, t_env *enviro)
{
	t_list	*tokens;
	(void)enviro;
	if (quote_checker(input) == -1)
		fprintf(stderr, "QUOTE_ERROR\n");
	tokens = build_tokens(input);
	while (tokens)
	{
		printf("\ttoken->value: "YELLOW"%s"RESET"\n\ttoken->type: %d\n",
			((t_token *)tokens->content)->value,
			((t_token *)tokens->content)->type);
		tokens = tokens->next;
	}
}

void	chose(t_env *enviro, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->fd_in != 0)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out != 0)
		dup2(cmd->fd_out, STDOUT_FILENO);
	fprintf(stderr, "name =%s\n", cmd->name);
	if (ft_strncmp(cmd->name, "exit", 4) == 0)
		exitfree(enviro);
	else if (ft_strncmp(cmd->name, "pwd", 3) == 0)
		pwd();
	else if (ft_strncmp(cmd->name, "env", 3) == 0)
		envi(enviro);
	else if (ft_strncmp(cmd->name, "export", 6) == 0)
		export(cmd, enviro);
	else if (ft_strncmp(cmd->name, "unset", 5) == 0)
	{
		while (cmd->arg[i])
		{
			unset(cmd->arg[i], enviro);
			i++;
		}
	}
	else if (ft_strncmp(cmd->name, "cd", 2) == 0)
	{
		cd(cmd->arg, enviro);
	}
	else if (ft_strncmp(cmd->name, "echo", 4) == 0)
	{
		echo(cmd->arg);
	}
	else if (ft_strncmp(cmd->name, "./", 2) == 0)
	{
		exed(cmd, enviro);
	}
	else
		lexe(cmd, enviro);
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (cmd->fd_out != 0)
		close(cmd->fd_out);
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

t_list	*test(void)
{
	t_list	*ret;
	t_list	*rat;
	t_token	*tok;

	ret = malloc(sizeof(t_list));
	rat = ret;
	tok = malloc(sizeof(t_token));
	tok->type = STR;
	tok->value = "export";
	ret->content = tok;
	ret->next = malloc(sizeof(t_list));
	ret = ret->next;
	tok = malloc(sizeof(t_token));
	tok->type = STR;
	tok->value = "a=coucou";
	ret->content = tok;
	ret->next = malloc(sizeof(t_list));
	ret = ret->next;
	tok = malloc(sizeof(t_token));
	tok->type = PIPE;
	tok->value = "";
	ret->content = tok;
	ret->next = malloc(sizeof(t_list));
	ret = ret->next;
	tok = malloc(sizeof(t_token));
	tok->type = STR;
	tok->value = "env";
	ret->content = tok;
	ret->next = NULL;
	return (rat);
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
		// cmd = readline("minishell% ");
		// if (cmd && ft_strlen(cmd) > 0)
		// 	add_history(cmd);
		// parser(cmd, enviro);
		dd(test(), enviro);
		break ;
		free(cmd);
	}
	return (0);
}
