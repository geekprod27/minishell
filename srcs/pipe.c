/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:20:42 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/07/07 11:40:56 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ipipe(int ltab, t_pipe *p)
{
	int	piper[2];

	if (pipe(piper) == -1)
		return (1);
	p->in = piper[1];
	p->out = piper[0];
	if (ltab > 1)
	{
		p->next = malloc(sizeof(t_pipe));
		p->next->prev = p;
		ltab = ltab - 1;
	}
	return (0);
}

t_pipe	*initpipe(char	**tab)
{
	int		ltab;
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
		if (ipipe(ltab, p))
			return (NULL);
		if (ltab > 1)
			ltab = ltab - 1;
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

	i = 0;
	pl = initpipe(retsplit);
	pld = pl;
	pipe2(retsplit, enviro, pl);
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
