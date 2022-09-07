/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   la.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 12:00:09 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/09/07 16:08:46 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	getnbstr(t_list	*list)
{
	int	i;

	i = 0;
	while (list)
	{
		if (((t_token *) list->content)->type == STR)
		{
			i++;
			list = list->next;
		}
		else
			break ;
	}
	return (i);
}

void	piped(t_cmd **listcmd, t_env *enviro)
{
	int	i;
	int	k;

	i = 0;
	while (listcmd[i])
	{
		listcmd[i]->pid = fork();
		if (listcmd[i]->pid == 0)
		{
			chose(enviro, listcmd, i);
			k = 0;
			while (listcmd[k])
			{
				freetab(listcmd[k]->arg);
				k++;
			}
			freetcmd(listcmd);
			exit(1);
		}
		i++;
	}
	i = 0;
	while (listcmd[i])
	{
		waitpid(listcmd[i]->pid, 0, 0);
		if (listcmd[i]->fd_in != 0)
			close(listcmd[i]->fd_in);
		if (listcmd[i]->fd_out != 1)
			close(listcmd[i]->fd_out);
		free(listcmd[i]);
		i++;
	}
	free(listcmd);
}

void	dd(t_list	*list, t_env *enviro)
{
	t_cmd	**listcmd;

	listcmd = initlistcmd(list);
	if (listcmd[1])
		piped(listcmd, enviro);
	else
		chose(enviro, listcmd, 0);
}

// if (tmp->type == STR && ((t_token *)(list->next->content))->type == STR)
// 	{
// 		cmd = tmp->value;
// 		list = list->next;
// 		tmp = (t_token *) list->content;
// 		arg = malloc(sizeof(char *) * (getnbstr(list) + 1));
// 		while (tmp->type == STR)
// 		{
// 			arg[i] = tmp->value;
// 			list = list->next;
// 			tmp = (t_token *) list->content;
// 			i++;
// 		}
// 		arg[i] = NULL;
// 		d.name = cmd;
// 		d.arg = arg;
// 		chose(enviro, &d);
// 	}

void	outfileapp(char *path, t_cmd *cmd)
{
	int		fd;
	char	*tmp;
	char	*tmp2;

	fd = open(path, O_CREAT);
	if (fd <= 0)
	{
		ft_putstr_fd("Open error\n", STDERR_FILENO);
		return ;
	}
	tmp = ft_strdup("");
	tmp2 = ft_strdup("");
	while (read(fd, tmp2, 1))
		tmp = ft_strjoinchar(tmp, tmp2[0]);
	ft_putstr_fd(tmp, fd);
	cmd->fd_out = fd;
}
