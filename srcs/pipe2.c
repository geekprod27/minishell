/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:36:39 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/07/07 11:41:02 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe2(char **retsplit, t_env *enviro, t_pipe *pl)
{
	int		i;
	char	*tmp;

	i = 0;
	while (retsplit[i])
	{
		if (retsplit[i][0] == ' ')
		{
			tmp = retsplit[i];
			retsplit[i] = ft_strtrim(tmp, " ");
			free(tmp);
		}
		pl->pid = fork();
		if (pl->pid == 0)
			childpipe(i, pl, retsplit, enviro);
		i++;
		if (pl->next)
			pl = pl->next;
	}
}

void	infile(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd <= 0)
	{
		ft_putstr_fd("Open error\n", STDERR_FILENO);
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	outfile(char *path)
{
	int	fd;

	fd = open(path, O_CREAT);
	if (fd <= 0)
	{
		ft_putstr_fd("Open error\n", STDERR_FILENO);
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

int	tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
