/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shocquen <shocquen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:29:25 by shocquen          #+#    #+#             */
/*   Updated: 2022/08/26 01:34:00 by shocquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static inline int	is_whitesp(char c);
// static inline int	is_spe(char *str);
t_token *newtok(char *value, t_type type);

t_list *build_tokens(char *restrict str)
{
	t_list	*tokens;
	char		*value;

	tokens = NULL;
	value	= sk_strtok(str, " ");
	while (value != NULL)
	{
		// printf("strtok: %s\n", value);
		ft_lstadd_back(&tokens, ft_lstnew(newtok(value, 0)));
		value = sk_strtok(NULL, " ");
	}
	// todo: tokenize_meta_char(&tokens) newtok on pipes, redirr..
	// todo: expand_tokens(&tokens, env)
	return (tokens);
}

// static inline int	is_whitesp(char c)
// {
// 	return (c == ' ' || c == '\t' || c == '\n');
// }

// static inline int	is_spe(char *str)
// {
// 	if ((*str == '>' || *str == '<') && *(str + 1) && *(str + 1) == *str)
// 		return ((int)*str + 1);
// 	if (*str == '|' || *str == '>' || *str == '<')
// 		return ((int)*str);
// 	return (0);
// }

t_token *newtok(char *value, t_type type)
{
	t_token	*ret;

	ret = ft_calloc(sizeof(*ret), 1);
	if (!ret)
		return (NULL);
	ret->value = ft_strdup(value);
	ret->type = type;
	return (ret);
}

/* static void *strtrim(char **str)
{
	void	*ptr;
	int		i;

	ptr = *str;
	i = 0;
	while (is_whitesp(**str))
		++*str;
	while ((*str)[i])
		++i;
	while (is_whitesp((*str)[--i]))
		;
	*(*str + i + 1) = 0;
	return (ptr);
} */
