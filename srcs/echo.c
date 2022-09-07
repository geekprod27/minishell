/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:22:10 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/09/07 15:53:30 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getname(char *cmd, int i)
{
	char	*name;

	name = ft_strdup("");
	while (cmd[i] != ' ' && cmd[i])
	{
		name = ft_strjoinchar(name, cmd[i]);
		i++;
	}
	return (name);
}

int	echo(char	**cmd)
{
	int		i;
	int		tiretn;

	i = 0;
	if (cmd[1][0] == '-' && cmd[1][1] == 'n')
	{
		tiretn = 1;
		i = 1;
		while (cmd[1][i] == 'n' && cmd[1][i])
			i++;
		if (cmd[1][i])
			tiretn = 0;
		i = tiretn + 1;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i+1])
			printf(" ");
		i++;
	}
	if (tiretn)
		return (0);
	printf("\n");
	return (0);
}

char	*getpath(char *cmd, t_env *enviro)
{
	char	*path;
	char	**pa;
	char	*name;

	int (i) = 0;
	path = getvale("PATH", enviro);
	pa = ft_split(path, ':');
	name = getna(cmd);
	while (pa[i])
	{
		path = ft_strjoin(pa[i], name);
		if (access(path, X_OK) == 0)
		{
			freetr(pa, name, i);
			return (path);
		}
		free(path);
		free(pa[i]);
		i++;
	}
	free(pa);
	free(name);
	return (NULL);
}

char	**getenvchar(t_env *enviro)
{
	int		i;
	char	**ret;

	i = 0;
	while (enviro->next)
	{
		enviro = enviro->next;
		i++;
	}
	ret = ft_calloc(i + 1, sizeof(char *));
	enviro = enviro->deb;
	i = 0;
	while (enviro->next)
	{
		ret[i] = ft_strdup(enviro->name);
		ret[i] = ft_strjoinchar(ret[i], '=');
		ret[i] = ft_strjoin_free1(ret[i], enviro->value);
		i++;
		enviro = enviro->next;
	}
	ret[i] = NULL;
	return (ret);
}

void	lexe(t_cmd *cmd, t_env *envi)
{
	int		pid;
	int		status;
	char	*path;
	char	**argv;
	char	**env;

	signal(SIGINT, childctrlc);
	signal(SIGQUIT, coredump);
	if (cmd->pid == -2)
		pid = fork();
	else
		pid = 0;
	if (pid == 0)
	{
		path = getpath(cmd->name, envi);
		argv = cmd->arg;
		if (path)
			argv[0] = path;
		env = getenvchar(envi);
		freeenv(envi);
		child(path, argv, env, cmd->name);
		free(cmd);
		exit(6);
	}
	else if (cmd->pid == -2)
		waitpid(pid, &status, 0);
}
