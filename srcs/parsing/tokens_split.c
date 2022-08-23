/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shocquen <shocquen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:29:25 by shocquen          #+#    #+#             */
/*   Updated: 2022/08/23 16:29:26 by shocquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static inline int	is_whitesp(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static inline int	is_spe(char *str)
{
	if ((*str == '>' || *str == '<') && *(str + 1) && *(str + 1) == *str)
		return ((int)*str + 1);
	if (*str == '|' || *str == '>' || *str == '<')
		return ((int)*str);
	return (0);
}

static void *strtrim(char **str)
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
}

t_token *mktok(char *value, size_t len, t_type type)
{
	t_token	*ret;

	ret = ft_calloc(sizeof(*ret), 1);
	if (!ret)
		return (NULL);
	ret->value = ft_strndup(value, len);
	ret->type = type;
	value = value + len;
	return (ret);
}

/* t_list *tokens_split(char *str)
{
	t_list	*ret;
	char		*start;
	t_type		type;

	ret = NULL;
	strtrim(&str);
	if (is_whitesp(*str))
		return (NULL);
	while (*str)
	{
		
		start = str;
		if (*str == '\'' || *str == '"')
		{
			str = ft_strchr(str + 1, *str);
		}
		else if (!is_whitesp(*str))
		{
			while (*str && !is_whitesp(*str) && !is_spe(str))
				++str;
			if (is_whitesp(*str) || is_spe(str))
			{
				type = (int)is_spe(str);
				*str = 0;
			}
		}
		if (!*start)
			break ;
		ft_lstadd_back(&ret, ft_lstnew(mktok(start, ++str - (start - 1), type)));
	}
	return (ret);
} */

t_list *tokens_split(char *str)
{
	t_list	*ret;
	char		*start;
	t_type		type;

	ret = NULL;
	strtrim(&str);
	if (is_whitesp(*str))
		return (NULL);
	while (*str)
	{
		start = str;
		if (!is_whitesp(*str))
		{
			while (*str && !is_whitesp(*str) && !is_spe(str))
			{
				if (*str == '\'' || *str == '"')
				{
					str = ft_strchr(str + 1, *str) + 1;
					break ;
				}
				++str;
			}
			if (is_whitesp(*str) || is_spe(str))
			{
				type = (int)is_spe(str);
				*str = 0;
			}
		}
		printf("split: %s\n", start);
		if (!*start)
			break ;
		ft_lstadd_back(&ret, ft_lstnew(mktok(start, ++str - (start - 1), type)));
	}
	return (ret);
}