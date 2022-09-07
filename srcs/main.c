/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 20:59:55 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/09/07 16:14:58 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(char *input, t_env *enviro)
{
	t_list	*tokens;
	t_list	*start;

	(void)enviro;
	if (quote_checker(input) == -1)
		fprintf(stderr, RED"QUOTE_ERROR\n"RESET);
	if (sk_strcspn(input, ";\\") < ft_strlen(input))
		fprintf(stderr, RED"SPECIAL_CHAR_ERROR\n"RESET);
	// todo: exit if error
	tokens = NULL;
	build_tokens(&tokens, input);
	start = tokens;
	while (tokens)
	{
		printf("\ttoken->value: "YELLOW"%s"RESET"\n\ttoken->type: %d\n",
			((t_token *)tokens->content)->value,
			((t_token *)tokens->content)->type);
		tokens = tokens->next;
	}
	free(start);
}

void	chose(t_env *enviro, t_cmd **cmd, int nbcmd)
{
	int	i;

	i = 0;
	dup2(cmd[nbcmd]->fd_in, STDIN_FILENO);
	dup2(cmd[nbcmd]->fd_out, STDOUT_FILENO);
	freeplc(cmd);
	if (ft_strncmp(cmd[nbcmd]->name, "exit", 4) == 0)
		exitfree(enviro);
	else if (ft_strncmp(cmd[nbcmd]->name, "pwd", 3) == 0)
		pwd();
	else if (ft_strncmp(cmd[nbcmd]->name, "env", 3) == 0)
		envi(enviro);
	else if (ft_strncmp(cmd[nbcmd]->name, "export", 6) == 0)
		export(cmd[nbcmd], enviro);
	else if (ft_strncmp(cmd[nbcmd]->name, "unset", 5) == 0)
	{
		while (cmd[nbcmd]->arg[i])
		{
			unset(cmd[nbcmd]->arg[i], enviro);
			i++;
		}
	}
	else if (ft_strncmp(cmd[nbcmd]->name, "cd", 2) == 0)
	{
		cd(cmd[nbcmd]->arg, enviro);
	}
	else if (ft_strncmp(cmd[nbcmd]->name, "echo", 4) == 0)
	{
		echo(cmd[nbcmd]->arg);
	}
	else if (ft_strncmp(cmd[nbcmd]->name, "./", 2) == 0)
	{
		exed(cmd[nbcmd], enviro);
	}
	else
		lexe(cmd[nbcmd], enviro);
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
	tok->type = IN_FILE;
	tok->value = "";
	ret->content = tok;
	ret->next = malloc(sizeof(t_list));
	ret = ret->next;
	tok = malloc(sizeof(t_token));
	tok->type = STR;
	tok->value = "grammar";
	ret->content = tok;
	ret->next = malloc(sizeof(t_list));
	ret = ret->next;
	tok = malloc(sizeof(t_token));
	tok->type = STR;
	tok->value = "grep";
	ret->content = tok;
	ret->next = malloc(sizeof(t_list));
	ret = ret->next;
	tok = malloc(sizeof(t_token));
	tok->type = STR;
	tok->value = "d";
	ret->content = tok;
	ret->next = NULL;
	return (rat);
}

int	main(int ac, char **av, char **env)
{
	//char	*cmd;
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
		//free(cmd);
	}
	return (0);
}
