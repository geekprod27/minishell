/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:59:46 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/05/12 12:18:17 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*initenv(char **env)
{
	t_env	*un;
	t_env	*deux;
	char	**retsplit;

	int (i) = 1;
	un = ft_calloc(1, sizeof(t_env));
	un->deb = un;
	un->next = NULL;
	retsplit = ft_split(env[0], '=');
	addele(un, retsplit);
	free(retsplit);
	while (env[i])
	{
		deux = un;
		un = ft_calloc(1, sizeof(t_env));
		un->deb = deux->deb;
		deux->next = un;
		un->next = NULL;
		retsplit = ft_split(env[i], '=');
		addele(un, retsplit);
		free(retsplit);
		i++;
	}
	return (un->deb);
}

char	*ft_strjoinchar(char const *s1, char const s2)
{
	int		i;
	int		len1;
	char	*dest;

	len1 = ft_strlen(s1);
	dest = malloc(sizeof(char) * (len1 + 2));
	if (!dest)
		return (0);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	i = 0;
	dest[len1] = s2;
	len1++;
	dest[len1] = '\0';
	free((char *)s1);
	return (dest);
}

char	*getvale(char *name, t_env *un)
{
	un = un->deb;
	while (un)
	{
		if (ft_strncmp(un->name, name, ft_strlen(name) + 1) == 0)
			return (un->value);
		un = un->next;
	}
	return (NULL);
}

void	changedeb(t_env *un)
{
	t_env	*deb;

	deb = un;
	while (un)
	{
		un->deb = deb;
		un = un->next;
	}
}

int	checkname(char *name)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(name[i]) || name[i] == '_'))
		return (0);
	i++;
	while (name[i])
	{
		if (!(ft_isalnum(name[i]) || name[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
