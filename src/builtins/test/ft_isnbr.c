/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnbr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 13:32:23 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/20 14:45:20 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_isnbr(char *str)
{
	int		num;
	int		sign;
	char	*ptr;

	num = 0;
	str = ft_strtrim(str);
	ptr = str;
	sign = 0;
	if (*str == '+' && (sign = 1))
		str++;
	if (!sign && *str == '-')
		str++;
	while (*str)
	{
		num = 1;
		if (!ft_isdigit(*str))
		{
			free(ptr);
			return (NULL);
		}
		str++;
	}
	return (ptr);
}
