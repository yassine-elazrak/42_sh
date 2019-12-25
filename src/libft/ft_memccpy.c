/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 21:48:19 by sid-bell          #+#    #+#             */
/*   Updated: 2018/10/10 16:25:14 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dest;
	unsigned char	*source;
	unsigned char	ch;

	ch = (unsigned char)c;
	source = (unsigned char*)src;
	dest = (unsigned char*)dst;
	while (n-- > 0)
	{
		*dest = *source;
		if (ch == *source)
			return (dest + 1);
		dest++;
		source++;
	}
	return (NULL);
}
