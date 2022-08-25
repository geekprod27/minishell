/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shocquen <shocquen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 20:59:55 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/08/26 01:51:01 by shocquen         ###   ########.fr       */
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

void	ctrlc(int i)
{
	signal(SIGINT, ctrlc);
	i = i + 5;
	rl_on_new_line();
	// rl_replace_line("", 1);
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
		parser(cmd, enviro);
		free(cmd);
	}
	return (0);
}
