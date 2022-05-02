/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 18:26:05 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/05/02 16:06:17 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*last;
	t_list	*item;
	void	*content;

	new_lst = NULL;
	last = NULL;
	while (lst)
	{
		content = f(lst->content);
		item = ft_lstnew(content);
		if (!item)
		{
			if (new_lst)
				ft_lstclear(&new_lst, del);
			return (NULL);
		}
		if (last)
			last->next = item;
		if (!new_lst)
			new_lst = item;
		last = item;
		lst = lst->next;
	}
	return (new_lst);
}
