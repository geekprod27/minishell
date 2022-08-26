/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shocquen <shocquen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:29:25 by shocquen          #+#    #+#             */
/*   Updated: 2022/08/26 18:54:24 by shocquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*newtok(char *value, t_type type);
void	restruct_quotes(t_list **tokens);
// static inline int	is_whitesp(char c);
// static inline int	is_spe(char *str);

void	build_tokens(t_list **tokens, char *restrict str)
{
	char		*value;

	value = sk_strmbtok(str, " ", "\"'", "\"'");
	while (value != NULL)
	{
		ft_lstadd_back(tokens, ft_lstnew(newtok(value, 0)));
		value = sk_strmbtok(NULL, " ", "\"'", "\"'");
	}
	// todo: tokenize_meta_char(&tokens) newtok on pipes, redirr..
	// todo: expand_tokens(&tokens, env)
}

t_token	*newtok(char *value, t_type type)
{
	t_token	*ret;

	ret = ft_calloc(sizeof(*ret), 1);
	if (!ret)
		return (NULL);
	ret->value = ft_strdup(value);
	ret->type = type;
	return (ret);
}

// static inline int	is_spe(char *str)
// {
// 	if ((*str == '>' || *str == '<') && *(str + 1) && *(str + 1) == *str)
// 		return ((int)*str + 1);
// 	if (*str == '|' || *str == '>' || *str == '<')
// 		return ((int)*str);
// 	return (0);
// }
