/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sk_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shocquen <shocquen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 00:27:24 by shocquen          #+#    #+#             */
/*   Updated: 2022/08/26 01:10:00 by shocquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	sk_strspn(char *str, char *span);
size_t	sk_strcspn(char *str, char *span);

char	*sk_strtok(char	*str, char *const sep)
{
	static char	*save;
	char		*end;

	if (!str)
		str = save;
	if (!*str)
		return ((save = str), NULL);
	str += sk_strspn(str, sep);
	if (!*str)
		return ((save = str), NULL);
	end = str + sk_strcspn(str, sep);
	if (!*end)
		return ((save = end), str);
	*end = 0;
	save = end + 1;
	return (str);
}

size_t	sk_strcspn(char *str, char *span)
{
	char	*end;
	char	*cmp;

	end = str;
	while (*end)
	{
		cmp = span;
		while (*cmp)
		{
			if (*end == *cmp)
				return (end - str);
			++cmp;
		}
		++end;
	}
	return (end - str);
}

size_t	sk_strspn(char *str, char *span)
{
	char	*end;
	char	*cmp;

	end = str;
	while (*end)
	{
		cmp = span;
		while (*cmp)
		{
			if (*end == *cmp)
				break ;
			++cmp;
		}
		if (*end != *cmp)
			break ;
		++end;
	}
	return (end - str);
}
