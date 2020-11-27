/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 01:12:33 by sid-bell          #+#    #+#             */
/*   Updated: 2018/10/12 01:39:34 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*source;
	char	*dest;
	size_t	i;

	dest = (char *)dst;
	source = (char *)src;
	i = 0;
	if (dest > source)
	{
		while (len--)
		{
			dest[len] = source[len];
		}
		return (dst);
	}
	while (i < len)
	{
		dest[i] = source[i];
		i++;
	}
	return (dst);
}
