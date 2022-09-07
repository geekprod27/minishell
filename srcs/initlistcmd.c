/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initlistcmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:22:07 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/09/07 16:09:08 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	**initlistcmd(t_list	*list)
{
	t_cmd	**listcmd;
	int		i;
	int		j;
	int		pi[2];

	i = 0;
	listcmd = malloc(sizeof(t_cmd *) * 2);
	listcmd[i] = malloc(sizeof(t_cmd));
	listcmd[i]->fd_out = 1;
	listcmd[i]->fd_in = 0;
	listcmd[i]->pid = -2;
	listcmd[i + 1] = NULL;
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
			listcmd[i]->arg[j] = NULL;
		}
		else if (((t_token *)list->content)->type == PIPE)
		{
			if (listcmd[i]->fd_out == 1)
			{
				if (pipe(pi) == -1)
					return (NULL);
				listcmd[i]->fd_out = pi[1];
				listcmd = licmdaddback(listcmd);
				i++;
				listcmd[i]->fd_in = pi[0];
				listcmd[i]->fd_out = 1;
				listcmd[i]->pid = -2;
			}
			list = list->next;
		}
	}
	return (listcmd);
}