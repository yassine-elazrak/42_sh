/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 05:47:25 by sid-bell          #+#    #+#             */
/*   Updated: 2018/10/14 17:10:47 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char *sub;
	char *str;

	sub = ft_strsub(haystack, 0, len);
	if (!(str = ft_strstr(sub, needle)))
		return (NULL);
	return ((char *)haystack + ft_strlen(sub) - ft_strlen(str));
}
