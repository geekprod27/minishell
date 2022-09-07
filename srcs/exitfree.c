/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitfree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:44:29 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/09/07 16:07:08 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exitfree(t_env *un)
{
	t_env	*deux;

	un = un->deb;
	while (un)
	{
		deux = un->next;
		free(un->name);
		free(un->value);
		free(un);
		un = deux;
	}
	exit(0);
}

void	freeenv(t_env *un)
{
	t_env	*deux;

	un = un->deb;
	while (un)
	{
		deux = un->next;
		free(un->name);
		free(un->value);
		free(un);
		un = deux;
	}
}

void	freeplc(t_cmd **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i]->fd_in != 0)
			close(cmd[i]->fd_in);
		if (cmd[i]->fd_out != 1)
			close(cmd[i]->fd_out);
		i++;
	}
}
