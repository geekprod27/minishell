/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shocquen <shocquen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 20:59:55 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/08/26 18:56:07 by shocquen         ###   ########.fr       */
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
		parser(cmd, enviro);
		free(cmd);
	}
	return (0);
}
