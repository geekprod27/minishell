/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fi.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:16:13 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/09/01 16:47:12 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	chldexed(t_cmd *cmde, t_env *envi)
{
	char	**argv;
	char	**env;
	char	*path;
	char	*cmd;

	argv = cmde->arg;
	cmd = argv[0];
	env = getenvchar(envi);
	path = ft_strdup(".");
	path = ft_strjoin_free1(path, cmd);
	freeenv(envi);
	argv[0] = path;
	if (execve(path, argv, env) == -1)
		printf("minishell: %s: No such file or directory\n", argv[0]);
	freetab(argv);
	freetab(env);
	exit(6);
}

void	exed(t_cmd *cmd, t_env *envi)
{
	int	pid;

	if (cmd->pid == -2)
		pid = fork();
	else
		pid = 0;
	if (pid == 0)
		chldexed(cmd, envi);
	else if (cmd->pid == -2)
		waitpid(pid, 0, 0);
}
