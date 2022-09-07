/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shocquen <shocquen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:39:30 by shocquen          #+#    #+#             */
/*   Updated: 2022/08/26 13:24:02 by shocquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_quote
{
	bool	simple;
	bool	first;
	int		count;
};

int	quote_checker(char *str)
{
	struct s_quote	quote;

	if (!str)
		return (0);
	quote.first = true;
	quote.count = 0;
	while (*str)
	{
		if (*str == '\\' && (str[1] == '\'' || str[1] == '\"'))
			str += 2;
		if ((*str == '\'' || *str == '\"') && quote.first)
		{
			quote.first = false;
			++quote.count;
			if (*str == '\'')
				quote.simple = true;
			else
				quote.simple = false;
		} else if (((*str == '\'' && quote.simple) || (*str == '\"' && !quote.simple)) && !quote.first)
		{
			quote.first = true;
			++quote.count;
		}
		++str;
	}
	if ((quote.count % 2))
		return (-1);
	return (quote.count / 2);
}

