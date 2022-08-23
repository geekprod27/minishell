/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   la.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 12:00:09 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/08/23 14:56:06 by nfelsemb         ###   ########.fr       */
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

void	dd(t_list	*list)
{
	t_token	*tmp;
	char	*cmd;
	char	**arg;
	int		i;

	tmp = (t_token *) list->content;
	i = 0;
	while (!(tmp->type == STR
			&& ((t_token *)(list->next->content))->type == STR))
	{
		if (tmp->type == STR
			&& ((t_token *)(list->next->content))->type == IN_FILE)
		{
			infile(tmp->value);
			list = list->next->next;
			tmp = (t_token *) list->content;
		}
		if (tmp->type == IN_HEREDOC
			&& ((t_token *)(list->next->content))->type == STR)
		{
			infile(heredoc(((t_token *)(list->next->content))->value));
			list = list->next->next;
			tmp = (t_token *) list->content;
		}
	}
	if (tmp->type == STR && ((t_token *)(list->next->content))->type == STR)
	{
		cmd = tmp->value;
		list = list->next;
		tmp = (t_token *) list->content;
		arg = malloc(sizeof(char *) * (getnbstr(list) + 1));
		while (tmp->type == STR)
		{
			arg[i] = tmp->value;
			list = list->next;
			tmp = (t_token *) list->content;
			i++;
		}
		arg[i] = NULL;
	}
	// GERER LES PIPES ICI
	while (list)
	{
		if (tmp->type == OUT_FILE)
		{
			outfile(((t_token *)(list->next->content))->value);
		}
		if (tmp->type == OUT_FILE_APPEND)
		{
			outfileapp(((t_token *)(list->next->content))->value);
		}
		list = list->next;
		tmp = (t_token *) list->content;
	}
}

void	outfileapp(char *path)
{
	int		fd;
	char	*tmp;
	char	*tmp2;
	int		i;

	i = -1;
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
	while (tmp[i++])
		ft_putchar_fd(tmp[i], fd);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
