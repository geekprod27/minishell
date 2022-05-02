/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 16:03:37 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/05/02 16:06:17 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token_to_lexer(t_lexer *lexer, const char *s, size_t len, t_ttype type)
{
	if (lexer_full(lexer))
		double_lexer(lexer);
	lexer->tokens[lexer->size] = malloc_token(s, len, type);
	lexer->size += 1;
}

void	add_word_to_lexer(t_lexer *lexer, char **token_s)
{
	add_token_to_lexer(lexer, *token_s, ft_strlen(*token_s), TOKEN_WORD);
	ft_strdel(*token_s, ft_strlen(*token_s));
}

void	handle_token(t_lexer *lexer, t_regex token, char **token_s)
{
	if (*token_s && token_s)
		add_word_to_lexer(lexer, token_s);
	if (token.type != TOKEN_PASS)
		add_token_to_lexer(lexer, token.op, token.len, token.type);
	lexer->pos += token.len;
}
