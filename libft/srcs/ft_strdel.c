/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 16:08:35 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/05/02 16:06:17 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdel(char *str, size_t n)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = NULL;
	ptr[0] = '\0';
	if (n > ft_strlen(str))
		str = ptr;
	else
	{
		while (str[i + n] != '\0')
		{
			ptr[i] = str[i + n];
			i++;
		}
		ptr[i] = '\0';
		str = ptr;
	}
	return (str);
}
