/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:39:28 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/05/02 16:06:17 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_flag_s(va_list va, int *p_char)
{
	char	*s;
	int		i;

	i = 0;
	s = va_arg(va, char *);
	if (s == NULL)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		*p_char += 6;
		return (0);
	}
	while (s[i])
		i++;
	if (write(1, s, i) == -1)
		return (-1);
	*p_char += i;
	return (0);
}
