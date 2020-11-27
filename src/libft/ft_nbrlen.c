/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 21:41:22 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/27 16:21:14 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nbrlen(long long int n, int base)
{
	size_t lenght;

	lenght = n <= 0 ? 1 : 0;
	while (n)
	{
		lenght++;
		n /= base;
	}
	return (lenght);
}
