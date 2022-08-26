/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fi.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:16:13 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/08/25 14:37:31 by nfelsemb         ###   ########.fr       */
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

	pid = fork();
	if (pid == 0)
		chldexed(cmd, envi);
	else
		waitpid(pid, 0, 0);
}
