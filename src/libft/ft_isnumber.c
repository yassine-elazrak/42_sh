/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 14:28:15 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/21 14:28:30 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_isnumber(char *str)
{
	int num;

	num = 0;
	while (*str)
	{
		num = 1;
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (num);
}
