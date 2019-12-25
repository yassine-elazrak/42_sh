/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 23:58:39 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/26 21:17:25 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		fill(char *str, long long int n, int lenght, int base)
{
	char				*bse;
	unsigned long long	un;

	un = n < 0 ? -n : n;
	bse = "0123456789abcdef";
	while (--lenght >= 0)
	{
		if (n < 0 && lenght == 0)
		{
			str[0] = '-';
			break ;
		}
		str[lenght] = bse[un % base];
		un /= base;
	}
}

char			*ft_itoa(long long int n, int base)
{
	char			*str;
	size_t			lenght;

	lenght = ft_nbrlen(n, base);
	if (!(str = (char *)malloc(sizeof(char) * (lenght + 1))))
		return (NULL);
	str[lenght] = '\0';
	fill(str, n, lenght, base);
	return (str);
}
