/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 21:48:19 by sid-bell          #+#    #+#             */
/*   Updated: 2018/10/08 19:03:26 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char *dest;
	char *source;

	dest = (char *)dst;
	source = (char *)src;
	while (n-- > 0)
	{
		*dest = *source;
		dest++;
		source++;
	}
	return (dst);
}
