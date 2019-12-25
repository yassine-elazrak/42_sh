/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 00:33:37 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/25 10:02:15 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long int	ft_atoi(const char *str)
{
	long long int	result;
	int				negative;
	unsigned int	i;

	result = 0;
	negative = 1;
	if (!str)
		return (0);
	while (ft_isspace(*str))
		str++;
	if (*str == '-' && (negative = -1))
		str++;
	if (negative == 1 && *str == '+')
		str++;
	i = *str - '0';
	while (i < 10)
	{
		result = 10 * result + i;
		str++;
		i = *str - '0';
	}
	if (result < 0)
		return (negative == -1 ? 0 : -1);
	return (result * negative);
}
