/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 23:01:31 by sid-bell          #+#    #+#             */
/*   Updated: 2018/10/17 23:01:34 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcount(char const *s, char const *s2)
{
	char	*str;
	size_t	count;
	size_t	lenght;

	lenght = 0;
	str = (char *)s;
	count = 0;
	while (*s2 && (str = ft_strstr(str + lenght, s2)))
	{
		count++;
		lenght = ft_strlen(s2);
	}
	return (count);
}
