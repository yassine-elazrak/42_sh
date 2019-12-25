/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 05:03:28 by sid-bell          #+#    #+#             */
/*   Updated: 2018/10/11 05:22:54 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;
	int		index;

	if (len == 0)
		return (dst);
	i = 0;
	index = 0;
	while (*src != '\0' && i < len)
	{
		dst[index] = *src;
		index++;
		src++;
		i++;
	}
	while (i < len)
	{
		dst[index++] = '\0';
		i++;
	}
	return (dst);
}
