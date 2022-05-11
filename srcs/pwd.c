/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:27:51 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/05/11 16:44:57 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	*buf;

	buf = ft_calloc(50, sizeof(char));
	getcwd(buf, 50);
	printf("%s\n", buf);
	free(buf);
	return (0);
}

int	envi(t_env *un)
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
	printf("%s", d);
	return (0);
}

int	export(char *cmd, t_env *un)
{
	un = un->deb;
	if (*cmd)
		return (exportd(cmd, un));
	else
		return (exportun(un));
	return (0);
}

int	unset(char *cmd, t_env *un)
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
	return (0);
}

int	cd(char	*cmd, t_env	*envi)
{
	char	**retsplit;

	int (i) = -1;
	if (!*cmd)
		cmd = getvale("HOME", envi);
	else
		cmd++;
	retsplit = ft_split(cmd, ' ');
	if (retsplit[1])
	{
		freetab(retsplit);
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	while (retsplit[i++])
		free(retsplit[i]);
	free(retsplit);
	if (chdir(cmd))
	{
		printf("%s: No such file or directory\n", cmd);
		return (1);
	}
	return (0);
}
