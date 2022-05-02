/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:28:42 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/05/02 16:06:17 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	create_token(const char *str, size_t len, t_ttype type)
{
	t_token	result;

	result.len = len;
	result.type = type;
	result.str = ft_newstr(len);
	ft_strlcpy(result.str, str, (len + 1));
	return (result);
}

t_token	*malloc_token(const char *s, size_t len, t_ttype type)
{
	t_token	*result;

	result = malloc(sizeof(t_token));
	if (!result)
		return (NULL);
	*result = create_token(s, len, type);
	return (result);
}

int	tokenize(t_lexer *lexer)
{
	t_regex token;
	char	*stack;

	stack = NULL;
	lexer->pos = 0;
	while (lexer->input[lexer->pos])
	{
		token = get_token(lexer->input + lexer->pos);
		/*need to handle quote + token + backslash + add char to stack*/
	}
	return (EXIT_SUCCESS);
}
