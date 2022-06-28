/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:20:42 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/06/23 12:28:58 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	freeplc(t_pipe *pl)
{
	t_pipe	*d;

	while (pl)
	{
		d = pl;
		pl = pl->next;
		close(d->in);
		close(d->out);
		free(d);
	}
}

t_pipe	*initpipe(char	**tab)
{
	int		ltab;
	int		piper[2];
	t_pipe	*p;
	t_pipe	*deb;

	ltab = tablen(tab);
	p = malloc(sizeof(t_pipe));
	p->prev = NULL;
	deb = p;
	if (!p)
		return (NULL);
	while (ltab > 0 && p)
	{
		if (pipe(piper) == -1)
			return (NULL);
		p->in = piper[1];
		p->out = piper[0];
		if (ltab > 1)
		{
			p->next = malloc(sizeof(t_pipe));
			p->next->prev = p;
			ltab = ltab - 1;
		}
		else
			p->next = NULL;
		p = p->next;
	}
	return (deb);
}

void	childpipe(int i, t_pipe *pl, char **retsplit, t_env *enviro)
{
	char	*tmp;

	if (i != 0)
		dup2(pl->prev->out, STDIN_FILENO);
	if (retsplit[i + 1])
		dup2(pl->in, STDOUT_FILENO);
	while (pl->prev)
		pl = pl->prev;
	freeplc(pl);
	tmp = ft_strdup(retsplit[i]);
	freetab(retsplit);
	parsing(tmp, enviro);
	freeenv(enviro);
	exit(1);
}

void	piped(char **retsplit, t_env *enviro)
{
	int		i;
	t_pipe	*pl;
	t_pipe	*pld;
	char	*tmp;

	i = 0;
	pl = initpipe(retsplit);
	pld = pl;
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
	while (pld)
	{
		waitpid(pld->pid, 0, 0);
		close(pld->in);
		if (pld->prev)
			close(pld->prev->out);
		pld = pld->next;
	}
	while (pl->prev)
		pl = pl->prev;
	freeplc(pl);
	freetab(retsplit);
}
