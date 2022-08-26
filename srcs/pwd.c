/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:27:51 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/08/25 14:28:31 by nfelsemb         ###   ########.fr       */
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

int	export(t_cmd *cmd, t_env *un)
{
	int	i;

	i = 0;
	un = un->deb;
	if (cmd->arg[0])
	{
		while (cmd->arg[i])
		{
			exportd(cmd->arg[i], un);
			i++;
		}
	}
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

int	cd(char	**cmd, t_env	*envi)
{
	int (i) = -1;
	if (!*cmd)
		cmd[0] = getvale("HOME", envi);
	if (cmd[1])
	{
		freetab(cmd);
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	if (chdir(cmd[0]))
	{
		printf("%s: No such file or directory\n", cmd[0]);
		return (1);
	}
	while (cmd[i++])
		free(cmd[i]);
	free(cmd);
	return (0);
}
