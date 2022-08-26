/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   la.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 12:00:09 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/08/26 13:27:01 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	getnbstr(t_list	*list)
{
	int	i;

	i = 0;
	while (((t_token *) list->content)->type == STR)
	{
		i++;
		list = list->next;
	}
	return (i);
}

void	dd(t_list	*list, t_env *enviro)
{
	t_cmd	**listcmd;
	int		i;
	int		j;
	int		pi[2];

	i = 0;
	listcmd = malloc(sizeof(t_cmd *) * 2);
	listcmd[i] = malloc(sizeof(t_cmd));
	while (list)
	{
		if (list->next)
		{
			if (((t_token *)list->content)->type == IN_FILE)
			{
				infile(((t_token *)list->next->content)->value, listcmd[i]);
				list = list->next->next;
			}
			else if (((t_token *)list->content)->type == IN_HEREDOC)
			{
				infile(heredoc(((t_token *)(list->next->content))->value), listcmd[i]);
				list = list->next->next;
			}
			else if (((t_token *)list->content)->type == OUT_FILE)
			{
				outfile(((t_token *)(list->next->content))->value, listcmd[i]);
				list = list->next->next;
			}
			else if (((t_token *)list->content)->type == OUT_FILE_APPEND)
			{
				outfileapp(((t_token *)(list->next->content))->value, listcmd[i]);
				list = list->next->next;
			}
		}
		if (((t_token *)list->content)->type == STR)
		{
			listcmd[i]->name = ((t_token *)list->content)->value;
			listcmd[i]->arg = malloc(sizeof(char *) * (getnbstr(list) + 1));
			j = 0;
			while (list && ((t_token *)list->content)->type == STR)
			{
				listcmd[i]->arg[j] = ((t_token *)list->content)->value;
				list = list->next;
				j++;
			}
		}
		else if (((t_token *)list->content)->type == PIPE)
		{
			if (listcmd[i]->fd_out == 1)
			{
				if (pipe(pi) == -1)
					return ;
				listcmd = licmdaddback(listcmd);
				listcmd[i]->fd_out = pi[0];
				i++;
				listcmd[i]->fd_in = pi[1];
			}
		}
	}
	(void) enviro;
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
