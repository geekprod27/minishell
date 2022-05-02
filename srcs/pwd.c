/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:27:51 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/04/28 14:13:58 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*pwd(void)
{
	char	*buf;

	buf = ft_calloc(50, sizeof(char));
	getcwd(buf, 50);
	buf = ft_strjoinchar(buf, '\n');
	return (buf);
}

char	*envi(t_env *un)
{
	char	*d;

	d = ft_strdup("");
	un = un->deb;
	while (un)
	{
		if (un->haveeq)
		{
			d = ft_strjoin_free1(d, un->name);
			d = ft_strjoinchar(d, '=');
			if (un->value)
				d = ft_strjoin_free1(d, un->value);
			d = ft_strjoinchar(d, '\n');
		}
		un = un->next;
	}
	return (d);
}

char	*export(char *cmd, t_env *un)
{
	un = un->deb;
	if (*cmd)
		return (exportd(cmd, un));
	else
		return (exportun(un));
	return (NULL);
}

void	unset(char *cmd, t_env *un)
{
	t_env	*prev;

	un = un->deb;
	prev = NULL;
	while (un)
	{
		if (ft_strncmp(un->name, cmd, ft_strlen(un->name) + 1) == 0)
		{
			if (prev)
			{
				prev->next = un->next;
			}
			else
				changedeb(un->next);
			free(un->name);
			free(un->value);
			free(un);
			break ;
		}
		prev = un;
		un = un->next;
	}
}

char	*cd(char	*cmd, t_env	*envi)
{
	char	**retsplit;
	int		i;

	if (!*cmd)
	{
		cmd = getvale("HOME", envi);
	}
	else
		cmd++;
	i = 0;
	retsplit = ft_split(cmd, ' ');
	if (retsplit[1])
	{
		freetab(retsplit);
		return (ft_strdup("minishell: cd: too many arguments\n"));
	}
	while (retsplit[i])
	{
		free(retsplit[i]);
		i++;
	}
	free(retsplit);
	if (chdir(cmd))
		return (ft_strjoin(cmd, ": No such file or directory\n"));
	return (0);
}
