/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:36:39 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/08/25 17:40:55 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe2(t_cmd **retsplit, t_env *enviro, t_pipe *pl)
{
	int		i;

	i = 0;
	while (retsplit[i])
	{
		pl->pid = fork();
		if (pl->pid == 0)
			childpipe(i, pl, retsplit, enviro);
		i++;
		if (pl->next)
			pl = pl->next;
	}
}

void	infile(char *path, t_cmd *cmd)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd <= 0)
	{
		ft_putstr_fd("Open error\n", STDERR_FILENO);
		return ;
	}
	cmd->fd_in = fd;
}

void	outfile(char *path, t_cmd *cmd)
{
	int	fd;

	fd = open(path, O_CREAT);
	if (fd <= 0)
	{
		ft_putstr_fd("Open error\n", STDERR_FILENO);
		return ;
	}
	cmd->fd_out = fd;
}

int	tablen(t_cmd **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
